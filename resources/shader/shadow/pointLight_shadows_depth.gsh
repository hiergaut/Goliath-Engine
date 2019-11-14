#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 shadowMatrices[6];

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec4 FragPos; // FragPos from GS (output per emitvertex)
out vec2 TexCoords;

//uniform bool has_texture_diffuse = false;
//uniform sampler2D texture_diffuse;

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
//            fTextCoords = TexCoords[i];
            TexCoords = gs_in[i].texCoords;
//            TexCoords = texelFetch(texture_diffuse, FragPos);
            gl_Position = shadowMatrices[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
} 
