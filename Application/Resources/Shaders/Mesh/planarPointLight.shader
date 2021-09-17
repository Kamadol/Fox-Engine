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

struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PlanarLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 u_camPos;
uniform vec3 u_camDir;
uniform Material u_material;
uniform PlanarLight u_planarLight;
uniform PointLight u_pointLight;

vec3 getPlanarLight(vec3 _normal, vec3 _viewDir, PlanarLight _light)
{
    //ambient
    vec3 ambient = _light.ambient * u_material.diffuse;

    //diffuse
    vec3 lightDir = normalize(-_light.direction);
    float diff = max(dot(_normal, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * u_material.diffuse;

    //specular
    vec3 reflectDir = reflect(-lightDir, _normal);
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = _light.specular * spec * u_material.specular;

    return ambient + diffuse + specular;
}
vec3 getPointLight(vec3 _fragPos, vec3 _normal, vec3 _viewPos, PointLight _light)
{
    //ambient
    vec3 ambient = _light.ambient * u_material.ambient;

    //diffuse 
    vec3 norm = normalize(_normal);
    vec3 lightDir = normalize(_light.position - _fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * u_material.diffuse;

    //specular
    vec3 viewDir = normalize(_viewPos - _fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = _light.specular * (spec * u_material.specular);

    return ambient + diffuse + specular;
}

void main()
{
    vec3 col = vec3(0.0);

    col += getPointLight(fragPos, normal, u_camPos, u_pointLight);
    col += getPlanarLight(normalize(normal), u_camDir, u_planarLight);

    FragColor = vec4(col, 1.0);
}
