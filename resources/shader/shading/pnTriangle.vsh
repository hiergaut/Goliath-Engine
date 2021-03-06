#version 410 core
                                                                                                
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 BoneIDs;
layout (location = 6) in vec4 Weights;

struct DirLight {
        vec3 direction;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        sampler2D shadowMap;
        mat4 lightSpaceMatrix;
        int id;
        float bias;
};
#define MAX_DIR_LIGHTS 2
uniform DirLight dirLight[MAX_DIR_LIGHTS];
uniform int nbDirLight;

struct PointLight {
        vec3 position;
        //        vec3 tangentPos;

        float constant;
        float linear;
        float quadratic;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        samplerCube shadowMap;
        //    int id;
        bool computed;
        float bias;
};
#define NR_POINT_LIGHTS 20
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int nbPointLight;


struct SpotLight {
        vec3 position;
        //        vec3 tangentPos;
        vec3 direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        sampler2D shadowMap;
        mat4 lightSpaceMatrix;
        int id;
        float bias;
};
#define MAX_SPOT_LIGHTS 4
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int nbSpotLight;



//out vec2 vs_out.TexCoords;

        out vec3 FragPos;
        out vec3 Normal;
        out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
//uniform mat4 lightSpaceMatrix;

uniform mat4 gBones[100];
uniform bool isSkeleton;

uniform mat2x4 u_bones[100];
uniform bool hasDualQuat = false;

mat2x4 GetBoneTransform(ivec4 joints, vec4 weights);
mat4 GetSkinMatrix();

//uniform sampler2D texture_normal;
uniform bool has_texture_normal = false;
uniform vec3 viewPos;
uniform bool has_texture_height = false;

void main()
{
        TexCoords = aTexCoords;
        //        vs_out.TexCoords.y = 1.0 - vs_out.TexCoords.y;
        //    vec3 normal;
        //    if (has_texture_normal) {
        //        normal = vec3(texture2D(texture_normal, vs_out.TexCoords));
        //    }
        //    else {
        //        normal = aNormal;
        //    }
        //        mat3 normalMatrix = transpose(inverse(mat3(model)));

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
//                mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
//                BoneTransform += gBones[BoneIDs[1]] * Weights[1];
//                BoneTransform += gBones[BoneIDs[2]] * Weights[2];
//                BoneTransform += gBones[BoneIDs[3]] * Weights[3];

                FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));

                //                            vs_out.Normal = model * BoneTransform * vec4(aNormal, 1.0);
                Normal = transpose(inverse(mat3(model * BoneTransform))) *  aNormal;
                //                vs_out.Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
        }
        else {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = transpose(inverse(mat3(model))) *  aNormal;
                //                                vs_out.Normal = mat3(transpose(inverse(model))) *  aNormal;
                //                vs_out.Normal = normalMatrix *  aNormal;

        }

        //        vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
        //        vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
        //        vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
        //        vs_out.TBN = mat3(T, B, N);

//        mat3 TBN = mat3(model);
//        if (has_texture_normal || has_texture_height) {
//                //                mat3 normalMatrix = transpose(inverse(mat3(model)));
//                //                vec3 T = normalize(normalMatrix * aTangent);
//                //                vec3 N = normalize(normalMatrix * aNormal);
//                //                T = normalize(T - dot(T, N) * N);
//                //                vec3 B = cross(N, T);

//                vec3 T   = normalize(mat3(model) * aTangent);
//                vec3 B   = normalize(mat3(model) * aBitangent);
//                vec3 N   = normalize(mat3(model) * aNormal);
//                TBN = transpose(mat3(T, B, N));


//                //                TBN = transpose(mat3(T, B, N));
//                //	vs_out.TangentLightPos = TBN * lightPos;
//                TangentViewPos  = TBN * viewPos;
//                TangentFragPos  = TBN * vs_out.FragPos;
//        }

        //        vec3 T = normalize(normalMatrix * aTangent);
        //        vec3 N = normalize(normalMatrix * aNormal);
        //        T = normalize(T - dot(T, N) * N);
        //        vec3 B = cross(N, T);
        //        mat3 vs_out.TBN = transpose(mat3(T, B, N));
        //    vs_out.Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
        //    vs_out.Normal = (model * BoneTransform * vec4(vs_out.Normal, 0.0)).xyz;
        //    vs_out.Normal = (model * vec4(vs_out.Normal, 0.0)).xyz;
//        for (int i =0; i <nbDirLight; ++i) {
//                //	    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
////                FragPosLightSpace[dirLight[i].id] = dirLight[i].lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
//                //        TangentLightPos[dirLight[i].id] = vs_out.TBN * dir;
//                //		vs_out.TangentLightPos[dirLight[i].id] = TBN * dirLight[i].position;
//        }
//        for (int i =0; i <nbPointLight; ++i) {
//                TangentLightPos[i] = TBN * pointLights[i].position;

//        }
//        for (int i =0; i <nbSpotLight; ++i) {
////                FragPosLightSpace[spotLights[i].id] = spotLights[i].lightSpaceMatrix * vec4(FragPos, 1.0);
//                //                spotLights[i].tangentPos = vs_out.TBN * spotLights[i].position;

//                TangentLightPos[i + nbPointLight] = TBN * spotLights[i].position;
//                TangentLightDir[i] = TBN * -spotLights[i].direction;
//        }
//        //        //    gl_Position = projection * view * vec4(vs_out.vs_out.FragPos, 1.0);

        //        TangentLightPos = vs_out.TBN * lightPos;
        //        TangentViewPos  = vs_out.TBN * viewPos;
        //        TangentFragPos  = vs_out.TBN * vs_out.FragPos;


        //        gl_Position = projection * view * model * vec4(aPos, 1.0);
        gl_Position = projection * view * vec4(FragPos, 1.0);
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
