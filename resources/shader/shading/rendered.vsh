#version 330 core
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

out VS_OUT {
        vec3 FragPos;
        vec3 Normal;
        vec2 TexCoords;
        vec4 FragPosLightSpace[2];

        //out vec3 TangentLightPos[10];
        //out vec3 TangentViewPos;
        //out vec3 TangentFragPos;
//        mat3 TBN;

        vec3 TangentLightPos[20];
        vec3 TangentViewPos;
        vec3 TangentFragPos;
        vec3 TangentLightDir[2];
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
//uniform mat4 lightSpaceMatrix;

uniform mat4 gBones[100];
uniform bool isSkeleton;

//uniform sampler2D texture_normal;
uniform bool has_texture_normal = false;
uniform vec3 viewPos;
uniform bool has_texture_height = false;

void main()
{
        vs_out.TexCoords = aTexCoords;
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
                mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
                BoneTransform += gBones[BoneIDs[1]] * Weights[1];
                BoneTransform += gBones[BoneIDs[2]] * Weights[2];
                BoneTransform += gBones[BoneIDs[3]] * Weights[3];

                vs_out.FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));

//                            vs_out.Normal = model * BoneTransform * vec4(aNormal, 1.0);
                vs_out.Normal = transpose(inverse(mat3(model * BoneTransform))) *  aNormal;
//                vs_out.Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
        }
        else {
                vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
                                vs_out.Normal = transpose(inverse(mat3(model))) *  aNormal;
//                                vs_out.Normal = mat3(transpose(inverse(model))) *  aNormal;
//                vs_out.Normal = normalMatrix *  aNormal;

        }

        //        vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
        //        vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
        //        vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
        //        vs_out.TBN = mat3(T, B, N);

        mat3 TBN = mat3(model);
        if (has_texture_normal || has_texture_height) {
//                mat3 normalMatrix = transpose(inverse(mat3(model)));
//                vec3 T = normalize(normalMatrix * aTangent);
//                vec3 N = normalize(normalMatrix * aNormal);
//                T = normalize(T - dot(T, N) * N);
//                vec3 B = cross(N, T);

                vec3 T   = normalize(mat3(model) * aTangent);
                    vec3 B   = normalize(mat3(model) * aBitangent);
                    vec3 N   = normalize(mat3(model) * aNormal);
                    TBN = transpose(mat3(T, B, N));


//                TBN = transpose(mat3(T, B, N));
        //	vs_out.TangentLightPos = TBN * lightPos;
                vs_out.TangentViewPos  = TBN * viewPos;
                vs_out.TangentFragPos  = TBN * vs_out.FragPos;
        }

        //        vec3 T = normalize(normalMatrix * aTangent);
        //        vec3 N = normalize(normalMatrix * aNormal);
        //        T = normalize(T - dot(T, N) * N);
        //        vec3 B = cross(N, T);
        //        mat3 vs_out.TBN = transpose(mat3(T, B, N));
        //    vs_out.Normal = mat3(transpose(inverse(model * BoneTransform))) *  aNormal;
        //    vs_out.Normal = (model * BoneTransform * vec4(vs_out.Normal, 0.0)).xyz;
        //    vs_out.Normal = (model * vec4(vs_out.Normal, 0.0)).xyz;
        for (int i =0; i <nbDirLight; ++i) {
                //	    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
                vs_out.FragPosLightSpace[dirLight[i].id] = dirLight[i].lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
                //        TangentLightPos[dirLight[i].id] = vs_out.TBN * dir;
//		vs_out.TangentLightPos[dirLight[i].id] = TBN * dirLight[i].position;
        }
        for (int i =0; i <nbPointLight; ++i) {
                vs_out.TangentLightPos[i] = TBN * pointLights[i].position;

        }
        for (int i =0; i <nbSpotLight; ++i) {
                vs_out.FragPosLightSpace[spotLights[i].id] = spotLights[i].lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
//                spotLights[i].tangentPos = vs_out.TBN * spotLights[i].position;

                vs_out.TangentLightPos[i + nbPointLight] = TBN * spotLights[i].position;
                vs_out.TangentLightDir[i] = TBN * -spotLights[i].direction;
        }
//        //    gl_Position = projection * view * vec4(vs_out.vs_out.FragPos, 1.0);

        //        TangentLightPos = vs_out.TBN * lightPos;
//        TangentViewPos  = vs_out.TBN * viewPos;
//        TangentFragPos  = vs_out.TBN * vs_out.FragPos;


//        gl_Position = projection * view * model * vec4(aPos, 1.0);
        gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}
