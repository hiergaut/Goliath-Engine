#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

//uniform sampler2D texture_diffuse1;

struct Material {
    vec3 ambient;
//    vec3 diffuse;
    vec3 specular;

    float shininess;
};

uniform Material material;
uniform vec3 viewPos;

void main()
{    
//    FragColor = vec4(1.0, 0, 0, 1.0);
//    return;

//    vec3 norm = normalize(Normal);
//    FragColor = vec4(norm * 0.5 + 0.5, 1.0);
//    FragColor = vec4(norm, 1.0);
//    return;

//    vec4 texColor = texture2D(texture_diffuse1, TexCoords);
//    if (texColor.a < 0.1)
//        discard;
//    FragColor = texColor;

//    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 ambient = material.ambient;

    vec3 norm = normalize(Normal);

//    vec3 diffuse = lightColor * material.diffuse;

    vec3 viewDir = normalize(viewPos - FragPos);
    float spec = pow(max(dot(viewDir, norm), 0.0), material.shininess);
    vec3 specular = spec * material.specular;

//    vec3 result = ambient + diffuse + specular;
    vec3 result = ambient + specular;
//    vec3 result = specular;

//    vec3 result = ambient;
////    result = vec3(1.0, 1.0, 1.0);

    FragColor = vec4(result, 1.0);
//    FragColor = vec4(material.ambient, 1.0);
}
