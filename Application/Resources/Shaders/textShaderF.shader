#version 330 core
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
