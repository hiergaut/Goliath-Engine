#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform float exposure;

//uniform bool active = false;
uniform float gamma = 2.2;

void main()
{             
//    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
//    FragColor = vec4(hdrColor, 1.0);
//    if (active)
//    int mipMap = 0;
//    vec4 color = (texture2D(scene, vec2(0.25, 0.25), mipMap) + texture2D(scene, vec2(0.75, 0.75), mipMap) + texture2D(scene, vec2(0.25, 0.75), mipMap) + texture2D(scene, vec2(0.75, 0.25), mipMap)) / 4.0;
//    float lum = dot(vec3(0.30, 0.59, 0.11), color.xyz);
//    float exposure = 0.5 / lum;
//            return;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    if(bloom)
        hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(hdrColor, 1.0);
//    FragColor = vec4(bloomColor, 1.0);
//    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
