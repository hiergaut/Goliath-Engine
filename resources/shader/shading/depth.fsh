#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;

float near = 0.01;
float far  = 50.0;

//in vec3 cubeCoords;
//uniform bool hasSkyBox = false;
uniform bool hasCubeMap = false;
uniform samplerCube cubeMap;
uniform vec3 cubeCenter;

uniform bool hasDepthMap = false;
uniform sampler2D depthMap;
//uniform vec3 cameraPos;
//bool hasCube;
uniform sampler2D texture_diffuse;
uniform bool has_texture_diffuse = false;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

uniform bool userColor = false;
uniform vec4 color;
void main()
{
        if (hasCubeMap) {
                //                vec3 I = normalize(cubeCenter - FragPos);
                vec3 I = normalize(FragPos - cubeCenter);
                //                I.x = -I.x;
                //                I.y = -I.y;
                //                I.z = -I.z;
                FragColor = vec4(texture(cubeMap, I).rgb, 1.0);
                return;
        }
        else if (hasDepthMap) {
                vec4 texColor = texture2D(depthMap, TexCoords);
                FragColor = texColor;
                return;
        }
        else if (has_texture_diffuse) {
                //                    if (has_texture_diffuse) {
                vec4 texColor = texture2D(texture_diffuse, TexCoords);
                if (texColor.a < 0.1) {
                        //                    gl_FragDepth = 0.9;
                        discard;
                }

                //                FragColor = texColor;
                //        float depth = LinearizeDepth(gl_FragCoord.z) / far; // division par far pour la démonstration
                //        FragColor = vec4(vec3(depth), 1.0);
                //                FragColor = vec4(1.0, 0.0, 0.0, 1.0);
                //                return;
        }
        else if (userColor) {
                FragColor = color;
                return;
        }



        float depth = LinearizeDepth(gl_FragCoord.z) / far; // division par far pour la démonstration
        FragColor = vec4(vec3(depth), 1.0);
}
