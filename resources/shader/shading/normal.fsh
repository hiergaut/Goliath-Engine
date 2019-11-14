#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in mat3 TBN;

//uniform sampler2D texture_diffuse1;

//struct Material {
//    vec3 ambient;
////    vec3 diffuse;
//    vec3 specular;

//    float shininess;
//};
uniform sampler2D texture_normal;
uniform bool has_texture_normal = false;
//uniform Material material;
//uniform vec3 viewPos;
//uniform bool contour = false;
uniform bool userColor = false;
uniform vec4 color;
uniform mat4 model;

void main()
{
        if (userColor) {
                FragColor = color;
                return;
        }

        vec3 normal;
        if (has_texture_normal) {
                normal = texture2D(texture_normal, TexCoords).rgb;
                normal = normalize(normal * 2.0 - 1.0);
//                normal.g = -normal.g;
                normal = normalize(TBN * normal);
//                viewDir = normalize(TangentViewPos - TangentFragPos);
//                normal = mat3(transpose(inverse(model))) *  normal;
//                normal = normalize(normal);
        }
        else {
                normal = normalize(Normal);
        }

        //    vec3 norm = normalize(Normal);
        FragColor = vec4(normal * 0.5 + 0.5, 1.0);
        //    FragColor = vec4(norm, 1.0);

}
