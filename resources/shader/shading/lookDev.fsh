#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};
uniform Material material;

uniform bool userColor = false;
uniform vec4 color;

uniform bool has_texture_diffuse = false;
uniform sampler2D texture_diffuse;

//in vec3 cubeCoords;
//uniform bool hasSkyBox = false;
//uniform bool hasCubeMap = false;
//uniform vec3 cameraPos;
//uniform samplerCube skybox;
//uniform vec3 cubeCenter;
//bool hasCube;
uniform sampler2D texture_opacity;
uniform bool has_texture_opacity = false;

void main()
{
//    hasCube = false;

//    if (hasCubeMap) {
//        vec3 I = normalize(FragPos - cubeCenter);
//        FragColor = vec4(texture(skybox, I).rgb, 1.0);
//    }
//    }
//    if (hasSkyBox) {
//        FragColor = texture(skybox, cubeCoords);
//        return;
//    }
    if (has_texture_opacity) {
            float opacity = texture2D(texture_opacity, TexCoords).r;
            if (opacity < 0.1) {
                discard;
            }
    }


    vec4 result;
    if (userColor) {
        result = color;
//        return;
    }
//    FragColor = vec4(1.0, 0, 0, 1.0);
//    return;

    //    vec3 norm = normalize(Normal);
    //    FragColor = vec4(norm * 0.5 + 0.5, 1.0);
    //    FragColor = vec4(norm, 1.0);
    //    return;

    else if (has_texture_diffuse) {
            vec4 texColor = texture2D(texture_diffuse, TexCoords);
            if (texColor.a < 0.5)
                    discard;

            result = texColor;
    }
    else {

            result = vec4(material.ambient, 1.0);

    }

    if (length(vec3(result)) < 0.01)
        discard;

    //    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    //    vec3 ambient = lightColor * material.ambient;

    //    vec3 norm = normalize(Normal);

    //    vec3 result = ambient;
////    result = vec3(1.0, 1.0, 1.0);

    FragColor = result;
//    FragColor = vec4(material.ambient, 1.0);
}
