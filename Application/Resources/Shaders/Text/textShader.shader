#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * aPos;
	texCoord = aTexCoord;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, texCoord);
    if (FragColor != vec4(0.0f, 0.0f, 0.0f, 1.0f))
        discard;
    //if (FragColor.x > 0.2f && FragColor.y > 0.2f && FragColor.z > 0.2f)
        //discard;
}
