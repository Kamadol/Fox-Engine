#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
    gl_Position = u_MVP * aPos;
    texCoord = aTexCoord;
    normal = mat3(transpose(inverse(u_model))) * aNormal;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;

uniform sampler2D texture0;

uniform vec3 u_lightColor = vec3( 1.0,  1.0, 1.0);
uniform vec3 u_lightPos   = vec3( 1.0,  1.0, 1.0);
uniform vec3 u_lightDir   = vec3(-1.0, -1.0, 1.0);

void main()
{
    //ambient
    float ambient = 0.2;

    //diffuse
    float diffuse = max(dot(normalize(normal), normalize(u_lightDir)), 0.0) * 0.5;

    //result
    vec3 result = (ambient + diffuse) * u_lightColor;
    FragColor = texture(texture0, texCoord) * vec4(result, 1.0);
}
