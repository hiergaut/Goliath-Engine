#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 BoneIDs;
layout (location = 6) in vec4 Weights;





out vec3 FragPos;
out vec3 Normal;
//out vec2 TexCoords;
out vec3 boneColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 gBones[100];
uniform bool isSkeleton;

int len = 3;
float lenf = len -1.0;

void main()
{
    if (isSkeleton) {
            mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
//            vec3 temp = BoneIDs[0];
//            vec3 color0 = transpose(BoneTransform)[0].xyz / 100.0;
//            vec3 color0 = BoneTransform[3].xyz;
            int id = BoneIDs[0];
            float r, g, b;
//            vec3 color0 = id % 3
            r = (id % len) / lenf;
            id /= 3;
            g = (id % len) / lenf;
            id /= 3;
            b = (id % len) / lenf;

            vec3 color0 = vec3(r, g, b);

            BoneTransform += gBones[BoneIDs[1]] * Weights[1];
            BoneTransform += gBones[BoneIDs[2]] * Weights[2];
            BoneTransform += gBones[BoneIDs[3]] * Weights[3];

            FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
//            Normal = model * BoneTransform * vec4(aNormal, 1.0);
            boneColor = color0;
    }
    else {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) *  aNormal;

            boneColor = vec3(1.0, 1.0, 1.0);
    }

    //    Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
    //    Normal = (model * BoneTransform * vec4(Normal, 0.0)).xyz;
    //    Normal = (model * vec4(Normal, 0.0)).xyz;
//    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
