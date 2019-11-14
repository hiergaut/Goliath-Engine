#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;
//layout (location = 3) in ivec4 BoneIDs;
//layout (location = 4) in vec4 Weights;




out vec3 FragPos;
out vec3 Normal;
//out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 gBones[100];
//uniform bool isSkeleton;

void main()
{
//    if (isSkeleton) {
//            mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
//            BoneTransform += gBones[BoneIDs[1]] * Weights[1];
//            BoneTransform += gBones[BoneIDs[2]] * Weights[2];
//            BoneTransform += gBones[BoneIDs[3]] * Weights[3];

//            FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));
//            Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
////            Normal = model * BoneTransform * vec4(aNormal, 1.0);
//    }
//    else {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) *  aNormal;
//    }

    //    Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
    //    Normal = (model * BoneTransform * vec4(Normal, 0.0)).xyz;
    //    Normal = (model * vec4(Normal, 0.0)).xyz;
//    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
