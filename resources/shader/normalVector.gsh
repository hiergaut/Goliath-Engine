#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.1;

out vec3 Normal;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
//    Normal = gs_in[index].normal;
//    Normal = vec3(-0.5, -0.5, -0.5);
    EmitVertex();

    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
//    Normal = gs_in[index].normal;
    EmitVertex();

    EndPrimitive();
}

void main()
{
//    GenerateLine(0); // première normale
//    GenerateLine(1); // deuxième normale
//    GenerateLine(2); // troisième normale

    vec4 source = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3;
    vec3 normal = normalize(gs_in[0].normal + gs_in[1].normal + gs_in[2].normal);

    float triangleSize = length(gl_in[0].gl_Position - source) + length(gl_in[1].gl_Position - source) + length(gl_in[2].gl_Position - source);

    gl_Position = source;
    Normal = normal;
//    Normal = gs_in[index].normal;
    EmitVertex();

    gl_Position = source + vec4(normal, 0.0) * MAGNITUDE * triangleSize;
    Normal = normal;
    EmitVertex();



}
