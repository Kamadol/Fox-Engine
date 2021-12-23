#version 330 core

VERTEX_SHADER
layout(location = 0) in vec2 aPos;

void main()
{
	gl_Position = vec4(aPos.xy, 0.0, 1.0);
}

FRAGMENT_SHADER
out vec4 FragColor;

uniform float u_time;
uniform vec2 u_screenSize;
uniform vec3 u_lightPos;
uniform mat4 u_camTransform;

uniform int u_steps;

#define MAX_STEPS 200
#define MAX_DIST 200.0
#define SURF_DIST 0.01

//utility
mat2 Rot(float a)
{
	float s = sin(a);
	float c = cos(a);

	return mat2(c, -s, s, c);
}
float smin(float a, float b, float k)
{
	float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
	return mix(b, a, h) - k * h * (1.0 - h);
}

//operations
vec3 OPrep(vec3 p, vec3 factor)
{
	return mod(p, factor) - 0.5 * factor;
}

//object distance functions
float sdSphere(vec3 p, float r) //d - distance
{
	return length(p) - r;
}
float sdCapsule(vec3 p, vec3 a, vec3 b, float r)
{
	vec3 ab = b - a;
	vec3 ap = p - a;

	float t = dot(ap, ab) / dot(ab, ab);
	t = clamp(t, 0.0, 1.0);

	vec3 c = a + t * ab;

	return length(p - c) - r;
}
float sdTorus(vec3 p, float R, float r)
{
	float x = length(p.xz) - R;
	return length(vec2(x, p.y)) - r;
}
float sdBox(vec3 p, vec3 s)
{
	vec3 q = abs(p) - s;
	return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}
float sdFractal001(vec3 p, vec3 size, int steps)
{
	vec3 cubeScale = vec3(3.0);

	for (int i = 0; i < steps; i++)
	{
		p *= cubeScale;  //scaling
		p = abs(p);     //mirroring
		p -= size * 2.0; //moving to corner
	}

	float d = sdBox(p, size) / pow(cubeScale.x, steps);

	return d;
}
float sdFractal002(vec3 p, vec3 size, int steps)
{
	vec3 cubeScale = vec3(3.0);

	for (int i = 0; i < steps; i++)
	{
		p *= cubeScale;  //scaling
		p = abs(p);      //mirroring
		p -= size * 2.0; //moving to corner
	}

	float d = sdSphere(p, size.x + p.x) / pow(cubeScale.x, steps);

	return d;
}

//searching lowest distance
float GetDist(vec3 p)
{
	float d = 0.0;

	float p1 = p.y;

	//d = sdFractal001(p - vec3(0.0, 2.0, 64.0), vec3(16.0), u_steps);
	//d = sdFractal001(p - vec3(0.0, 2.0, 64.0), vec3(16.0), u_steps);
	//d = sdFractal001(OPrep(p, vec3(30.0)), vec3(6.0), u_steps);

	d = p1;
	//d = sdFractal001(p, vec3(6.0), u_steps);
	//d = sdSphere(OPrep(p, vec3(5.0, 5.0, 5.0)), 1.0);

	return d;
}

//ray marcher function
float RayMarch(vec3 ro, vec3 rd)
{
	float dO = 0.0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 p = ro + rd * dO;
		float dS = GetDist(p);
		dO += dS;
		if (dO > MAX_DIST || dS < SURF_DIST)
			break;
	}

	return dO;
}

//find normal
vec3 GetNormal(vec3 p)
{
	vec2 e = vec2(0.01, 0.0);
	float d = GetDist(p);

	vec3 n = vec3(
		d - GetDist(p - e.xyy),
		d - GetDist(p - e.yxy),
		d - GetDist(p - e.yyx));
	return normalize(n);
}

//lighting
float GetLight(vec3 p)
{
	float diffuse = 0.0;
	vec3 n = GetNormal(p);

	//point light
	vec3 lightPos = u_lightPos;
	vec3 l = normalize(lightPos - p);
	diffuse += clamp(dot(l, n), 0.0, 1.0);

	//shadow
	float d = RayMarch(p + n * SURF_DIST * 2.0, l);
	if (d < length(lightPos - p))
		diffuse *= 0.2f;

	////planar light
	//vec3 lightDir = normalize(vec3(1.0, -1.0, 1.0));
	//diffuse += clamp(dot(-lightDir, n), 0.0, 1.0);

	////shadow
	//float d = RayMarch(p + n * SURF_DIST * 2.0, -lightDir);
	//if (d < MAX_DIST)
	//    diffuse *= 0.2f;

	return diffuse;
}

//camera
vec3 GetRayDir(vec3 ro)
{
	vec2 uv = (gl_FragCoord.xy - 0.5 * u_screenSize.xy) / u_screenSize.y;

	vec4 i = u_camTransform * vec4(uv.x, uv.y, 1.0, 1.0);
	vec3 rayDir = normalize(i.xyz - ro);

	return rayDir;
}

//MANDELBROT SET TESTS
#define MANDEL_STEPS 100.0
#define MANDEL_MAX_DIST 1000.0
#define MANDEL_MIN_DIST 0.0001
vec2 complexMul(vec2 a, vec2 b)
{
	return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
vec2 complexExp(vec2 a, float b)
{
	float len = length(a);
	float arg = atan(a.y, a.x);

	return pow(len, b) * vec2(cos(arg * b), sin(arg * b));
}

void main()
{
	/*
	vec3 col = vec3(0);

	vec3 ro = u_camTransform[3].xyz;

	vec3 rayDir = GetRayDir(ro);
	float d = RayMarch(ro, rayDir);
	vec3 p = ro + rayDir * d;

	//output color
	float diffuse = GetLight(p);

	col = vec3(diffuse) + vec3(0.1);
	FragColor = vec4(col, 1.0);
	if(d > MAX_DIST)
		FragColor = vec4(0.1, 0.3, 1.0, 1.0);
	*/

	/*
	vec2 uv = gl_FragCoord.xy / u_screenSize.xy; //(0, 0) -> (1, 1)
	uv.x *= 3.0; //(0, 0) -> (3, 1)
	uv.x -= 2.0; //(-2, 0) -> (1, 1)
	uv.y *= 2.0; //(-2, 0) -> (1, 2)
	uv.y -= 1.0; //(-2, -1) -> (1, 1)

	vec2 z = vec2(0.0);
	float it = 0.0;
	for (int i = 0; i < MANDEL_STEPS; i++)
	{
		z = complexMul(z, z) + uv.xy;
		if (length(z) > MANDEL_MAX_DIST)
		{
			FragColor = vec4(0.0, 0.0, (it + 20.0) / MANDEL_STEPS, 1.0);
			return;
		}

		it++;
	}

	FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	*/
	vec2 uv = gl_FragCoord.xy / u_screenSize.xy; //(0, 0) -> (1, 1)
	uv -= vec2(0.5); //(-0.5, -0.5) -> (0.5, 0.5)
	uv *= 4.0; //(-2.0, -2.0) -> (2.0, 2.0) //zakres dla ktorego liczymy punkty w liczbach zespolonych. Pomnozenie przez wieksza wartosc oddala kamere

	vec2 c = 0.7 * vec2(cos(u_time / 2.0), sin(u_time / 2.0)); //to mozna modyfikowac dla innych efektow. u_time daje efekt, ze cos zmienia sie z czasem
	vec2 z = uv;
	float it = 0.0;
	for (int i = 0; i < MANDEL_STEPS; i++)
	{
		z = complexExp(z, 2) + c; //tutaj mozna modyfikowac z po prawej stronie rownania. + c chyba powinno byc zawsze zachowane
		if (length(z) > MANDEL_MAX_DIST)
		{
			FragColor = vec4(0.0, 0.0, (it + 40.0) / MANDEL_STEPS, 1.0);
			return;
		}

		it++;
	}

	FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}
