#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 u_MVP = mat4(1.0);

void main()
{
    gl_Position = u_MVP * aPos;
    ourColor = aColor;
    texCoord = aTexCoord;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D texture0;

void main()
{
    vec4 col = texture(texture0, texCoord);
    FragColor = col;
}
