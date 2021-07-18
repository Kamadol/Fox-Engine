#version 330 core

out vec4 color;

float circleShape(vec2 position, float radius)
{
	return step(radius, length(position - vec2(0.5)));
}

void main()
{
	vec2 position = gl_FragCoord.xy / 800.0;

	float circle = circleShape(position, 0.2);

	vec3 color = vec3(circle);

	gl_FragColor = vec4(color, 1.0);
}
