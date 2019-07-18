#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

//out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//        Normal = normalize(vec4(aNormal, 1.0) * model).xyz;
//        Normal = aNormal;

//        Normal = transpose(inverse(mat3(model))) * aNormal;
        Normal = mat3(transpose(inverse(model))) * aNormal;

//        ourColor = aColor;
        TexCoord = vec2(aTexCoord);
        FragPos = vec3(model * vec4(aPos, 1.0));

        gl_Position = projection * view * vec4(FragPos, 1.0);
};
