#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 BoneIDs;
layout (location = 6) in vec4 Weights;





out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 gBones[100];
uniform bool isSkeleton;

//uniform sampler2D texture_normal;
//uniform bool has_texture_normal = false;

void main()
{
        vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
        vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
        T = normalize(T - dot(T, N) * N);
//        vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
        vec3 B = cross(N, T);
        TBN = mat3(T, B, N);

        TexCoords = aTexCoords;
        //    vec3 normal;
        //    if (has_texture_normal) {
        //        normal = vec3(texture2D(texture_normal, TexCoords));
        //    }
        //    else {
        //        normal = aNormal;
        //    }

        //void main()
        //{
        if (isSkeleton) {
                mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
                BoneTransform += gBones[BoneIDs[1]] * Weights[1];
                BoneTransform += gBones[BoneIDs[2]] * Weights[2];
                BoneTransform += gBones[BoneIDs[3]] * Weights[3];

                FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
                //            Normal = model * BoneTransform * vec4(aNormal, 1.0);
        }
        else {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(model))) *  aNormal;
        }

        //    Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
        //    Normal = (model * BoneTransform * vec4(Normal, 0.0)).xyz;
        //    Normal = (model * vec4(Normal, 0.0)).xyz;
        //    TexCoords = aTexCoords;

        gl_Position = projection * view * vec4(FragPos, 1.0);
        //    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
