#version 330 core
in vec4 FragPos;
in vec2 TexCoords;
//in vec2 fTexCoords;

uniform vec3 lightPos;
uniform float far_plane;

uniform bool has_texture_diffuse = false;
uniform sampler2D texture_diffuse;

void main()
{
    if (has_texture_diffuse) {
            vec4 texColor = texture2D(texture_diffuse, TexCoords);
            if (texColor.a < 0.5)
                    discard;
    }

    float lightDistance = length(FragPos.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}
