#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

//out vec3 ourColor;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//        Normal = normalize(vec4(aNormal, 1.0) * model).xyz;

//        Normal = transpose(inverse(mat3(model))) * aNormal;
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
//        Normal = aNormal;

//        ourColor = aColor;
        TexCoords = vec2(aTexCoords);

        gl_Position = projection * view * vec4(FragPos, 1.0);
};
