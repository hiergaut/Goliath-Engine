#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    vec4 texColor = texture2D(texture_diffuse1, TexCoords);
    if (texColor.a < 0.1)
        discard;
    FragColor = texColor;
}
