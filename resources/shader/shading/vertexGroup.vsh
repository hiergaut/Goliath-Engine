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

uniform mat2x4 u_bones[100];
uniform bool hasDualQuat = false;

mat2x4 GetBoneTransform(ivec4 joints, vec4 weights);
mat4 GetSkinMatrix();

int len = 3;
float lenf = len -1.0;

void main()
{
    if (isSkeleton) {
            mat4 BoneTransform;
            if (hasDualQuat) {
                    BoneTransform = GetSkinMatrix();
            }
            else {
                    BoneTransform= gBones[BoneIDs[0]] * Weights[0];
                    BoneTransform += gBones[BoneIDs[1]] * Weights[1];
                    BoneTransform += gBones[BoneIDs[2]] * Weights[2];
                    BoneTransform += gBones[BoneIDs[3]] * Weights[3];
            }
//            mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
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

//            BoneTransform += gBones[BoneIDs[1]] * Weights[1];
//            BoneTransform += gBones[BoneIDs[2]] * Weights[2];
//            BoneTransform += gBones[BoneIDs[3]] * Weights[3];

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


mat2x4 GetBoneTransform(ivec4 joints, vec4 weights)
{
    float sum_weight = weights.x + weights.y + weights.z + weights.w;

    // Fetch bones
    mat2x4 dq0 = u_bones[joints.x];
    mat2x4 dq1 = u_bones[joints.y];
    mat2x4 dq2 = u_bones[joints.z];
    mat2x4 dq3 = u_bones[joints.w];

    // Ensure all bone transforms are in the same neighbourhood
    weights.y *= sign(dot(dq0[0], dq1[0]));
    weights.z *= sign(dot(dq0[0], dq2[0]));
    weights.w *= sign(dot(dq0[0], dq3[0]));

    // Blend
    mat2x4 result =
        weights.x * dq0 +
        weights.y * dq1 +
        weights.z * dq2 +
        weights.w * dq3;

    result[0][3] += int(sum_weight < 1) * (1 - sum_weight);

    // Normalise
    float norm = length(result[0]);
    return result / norm;
}
mat4 GetSkinMatrix()
{
    mat2x4 bone = GetBoneTransform(BoneIDs, Weights);

    vec4 r = bone[0];
    vec4 t = bone[1];

    return mat4(
        1.0 - (2.0 * r.y * r.y) - (2.0 * r.z * r.z),
              (2.0 * r.x * r.y) + (2.0 * r.w * r.z),
              (2.0 * r.x * r.z) - (2.0 * r.w * r.y),
        0.0,

              (2.0 * r.x * r.y) - (2.0 * r.w * r.z),
        1.0 - (2.0 * r.x * r.x) - (2.0 * r.z * r.z),
              (2.0 * r.y * r.z) + (2.0 * r.w * r.x),
        0.0,

              (2.0 * r.x * r.z) + (2.0 * r.w * r.y),
              (2.0 * r.y * r.z) - (2.0 * r.w * r.x),
        1.0 - (2.0 * r.x * r.x) - (2.0 * r.y * r.y),
        0.0,

        2.0 * (-t.w * r.x + t.x * r.w - t.y * r.z + t.z * r.y),
        2.0 * (-t.w * r.y + t.x * r.z + t.y * r.w - t.z * r.x),
        2.0 * (-t.w * r.z - t.x * r.y + t.y * r.x + t.z * r.w),
        1);
}
