#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;
//out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
//	FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
}
