#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 boneColor;


//uniform bool contour = false;

uniform bool userColor = false;
uniform vec4 color;
void main()
{    
    if (userColor) {
        FragColor = color;
        return;
    }

//    if (contour) {
//        FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);

//        return;
//    }

//    vec3 result = ambient;
////    result = vec3(1.0, 1.0, 1.0);

//    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = vec4(boneColor, 1.0);
//    FragColor = vec4(material.ambient, 1.0);
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

//    vec3 ambient = lightColor * material.ambient;

//    vec3 norm = normalize(Normal);

//    vec3 result = ambient;
////    result = vec3(1.0, 1.0, 1.0);

////    FragColor = vec4(result, 1.0);
//    FragColor = vec4(material.ambient, 1.0);
}
