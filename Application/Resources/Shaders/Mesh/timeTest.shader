#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	gl_Position = u_MVP * aPos;
	texCoord = aTexCoord;
	fragPos = vec3(u_model * aPos);
	normal = mat3(transpose(inverse(u_model))) * aNormal;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float time;
uniform vec2 screenSize;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    //ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    //specular
    float specularStrength = 0.7f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    //result
    vec2 coord = (gl_FragCoord.xy / screenSize.xy);
    //vec2 coord = gl_FragCoord.xy;
    float color = 0.0f;
    color += sin(coord.x * 50.0f + cos(time + coord.y * 10.0f));
    color += cos(coord.x * 30.0f - sin(time + coord.y * 20.0f));
    color += cos(coord.x * 80.0f - sin(time + coord.y * 5.0f));
    color += cos(coord.x * 5.0f - sin(time + coord.y * 40.0f));
    color += cos(coord.x * 15.0f - sin(time + coord.y * 70.0f));
    color = (color + 1.0f) * 0.5f;

    vec3 result = (ambient + diffuse + specular) * vec3(color);
    FragColor = vec4(result, 1.0f);
}
