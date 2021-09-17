#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 u_MVP;

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
uniform sampler2D texture1;

void main()
{
    //FragColor = texture(texture0, texCoord) * ourColor;

    //FragColor = texture(texture0, texCoord);

    //FragColor = vec4(vec3(1.0f - texture(texture0, texCoord)), 1.0f);

    //FragColor = texture(texture0, texCoord);
    //float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    //FragColor = vec4(average, average, average, 1.0);

    float offset = 1.0 / 1000.0;
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // top-left
        vec2(0.0f, offset), // top-center
        vec2(offset, offset), // top-right
        vec2(-offset, 0.0f),   // center-left
        vec2(0.0f, 0.0f),   // center-center
        vec2(offset, 0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f, -offset), // bottom-center
        vec2(offset, -offset)  // bottom-right    
        );

    float kernel[9] = float[](
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
        );
    /*float kernel[9] = float[](
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
        ); */
        /*float kernel[9] = float[](
            2, -1, 2,
            -1, 5, -1,
            2, -1, 2
            );*/


    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture0, texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    FragColor = vec4(col, 1.0);
}
