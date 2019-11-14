#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;
in vec3 Normal;
//in vec3 FragPos;

//uniform sampler2D texture_diffuse1;

//struct Material {
//    vec3 ambient;
////    vec3 diffuse;
//    vec3 specular;

//    float shininess;
//};
//uniform Material material;
//uniform vec3 viewPos;

void main()
{    
    vec3 norm = normalize(Normal);
//    FragColor = vec4(norm * 0.5 + 0.5, 1.0);
//    FragColor = vec4(norm, 1.0);
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
//    return;

}
