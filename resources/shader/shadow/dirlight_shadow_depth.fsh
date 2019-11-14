#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform bool has_texture_diffuse = false;
uniform sampler2D texture_diffuse;

void main()
{
    if (has_texture_diffuse) {
            vec4 texColor = texture2D(texture_diffuse, TexCoords);
            if (texColor.a < 0.5)
                    discard;
    }

//     gl_FragDepth = gl_FragCoord.z;

//    FragColor = vec4(vec3(gl_FragCoord.z));
}

//#version 330 core
//out vec4 FragColor;

//in vec3 Normal;
//in vec3 FragPos;

//float near = 300;
//float far  = 500.0;

//float LinearizeDepth(float depth)
//{
//    float z = depth * 2.0 - 1.0; // back to NDC
//    return (2.0 * near * far) / (far + near - z * (far - near));
//}

//void main()
//{
//    float depth = LinearizeDepth(gl_FragCoord.z) / far; // division par far pour la démonstration
//    FragColor = vec4(vec3(depth), 1.0);
////    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
////    vec3 norm = normalize(Normal);
////    FragColor = vec4(norm * 0.5 + 0.5, 1.0);
//}
