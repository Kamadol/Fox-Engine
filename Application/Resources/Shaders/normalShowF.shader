#version 330 core
out vec4 FragColor;

in vec3 normal;

void main()
{
    //FragColor = vec4((normal.x + 1.0f) * 0.5f, (normal.y + 1.0f) * 0.5f, (normal.z + 1.0f) * 0.5f, 1.0f);
    FragColor = vec4(normal.xyz, 1.0f);
}
