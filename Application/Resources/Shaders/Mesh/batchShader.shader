#version 330 core

VERTEX_SHADER
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aOffset;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 u_camera;

void main()
{
    gl_Position = u_camera * vec4(aPos + aOffset, 1.0);
    texCoord = aTexCoord;
    fragPos = vec3(aPos);
    normal = aNormal;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture0;

void main()
{
    vec3 lightDir = vec3(1.0, -1.0, 1.0);
    float ambient = 0.2;
    float diff = max(dot(normal, -lightDir), 0.0) * 0.7;

    FragColor = texture(texture0, texCoord) * (ambient + diff);
}
