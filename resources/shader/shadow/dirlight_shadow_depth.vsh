#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

out vec3 FragPos;
out vec2 TexCoords;
//out vec3 Normal;

void main()
{
    TexCoords = aTexCoords;

    FragPos = vec3(model * vec4(aPos, 1.0));
//    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = lightSpaceMatrix * vec4(FragPos, 1.0);
//    gl_TextCoord = TexCoords;
}
