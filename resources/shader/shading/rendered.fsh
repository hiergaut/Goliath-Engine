#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
//layout(early_fragment_tests) in;


vec3 gridSamplingDisk[20] = vec3[]
                (
                vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

struct Material {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        float shininess;
};
//struct Material {
//    sampler2D diffuse;
//    sampler2D specular;
//    float shininess;
//};
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


//out vec4 FragColor;

in VS_OUT {
        in vec3 FragPos;
        in vec3 Normal;
        in vec2 TexCoords;
        in vec4 FragPosLightSpace[10];
        //} fs_in;
        //        in mat3 TBN;
        in vec3 TangentLightPos[10];
        in vec3 TangentViewPos;
        in vec3 TangentFragPos;
        vec3 TangentLightDir[5];
} fs_in;


//in vec3 fs_in.FragPos;
//in vec3 fs_in.Normal;
//in vec2 fs_in.TexCoords;

uniform sampler2D texture_diffuse;
uniform bool has_texture_diffuse = false;
//uniform sampler2D shadowMap;
uniform sampler2D texture_normal;
uniform bool has_texture_normal = false;

uniform sampler2D texture_specular;
uniform bool has_texture_specular = false;

uniform sampler2D texture_opacity;
uniform bool has_texture_opacity = false;

uniform sampler2D texture_height;
uniform bool has_texture_height = false;

//uniform bool hasTexture = false;

uniform Material material;

uniform vec3 viewPos;


uniform bool userColor = false;
uniform vec4 color;

uniform bool shadow = true;
//uniform bool disableFragmentShader = true;

//unifloat far_plane = 1000;
float far_plane = 5000;

uniform float heightScale = 1.0;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec2 texCoords);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 lightDir, vec2 texCoords);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 lightDir, vec2 texCoords, vec3 lightDir2);
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, DirLight light);
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, SpotLight light);
float ShadowCalculation(vec3 fragPos, vec3 normal, PointLight light);

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
        float height =  texture2D(texture_height, texCoords).r;
        return texCoords - viewDir.xy * (height * heightScale);
}

vec2 ParallaxMapping2(vec2 texCoords, vec3 viewDir)
{
        // number of depth layers
        const float minLayers = 8;
        const float maxLayers = 32;
        float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
        // calculate the size of each layer
        float layerDepth = 1.0 / numLayers;
        // depth of current layer
        float currentLayerDepth = 0.0;
        // the amount to shift the texture coordinates per layer (from vector P)
        vec2 P = viewDir.xy / viewDir.z * heightScale;
        vec2 deltaTexCoords = P / numLayers;

        // get initial values
        vec2  currentTexCoords     = texCoords;
        float currentDepthMapValue = texture2D(texture_height, currentTexCoords).r;

        while(currentLayerDepth < currentDepthMapValue)
        {
                // shift texture coordinates along direction of P
                currentTexCoords -= deltaTexCoords;
                // get depthmap value at current texture coordinates
                currentDepthMapValue = texture2D(texture_height, currentTexCoords).r;
                // get depth of next layer
                currentLayerDepth += layerDepth;
        }

        // get texture coordinates before collision (reverse operations)
        vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

        // get depth after and before collision for linear interpolation
        float afterDepth  = currentDepthMapValue - currentLayerDepth;
        float beforeDepth = texture2D(texture_height, prevTexCoords).r - currentLayerDepth + layerDepth;

        // interpolation of texture coordinates
        float weight = afterDepth / (afterDepth - beforeDepth);
        vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

        return finalTexCoords;
}


void main()
{
        //        if (disableFragmentShader) {
        //                FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        //                return;
        //        }
        //    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
        vec3 result = vec3(0.0f, 0.0f, 0.0f);

        //    return;
        //    FragColor = vec4(dirLight[0].ambient * material.specular, 1.0);
        if (userColor) {
                //                FragColor = color;
                result = vec3(color);
        }
        else {
                vec3 viewDir;
                if (has_texture_normal || has_texture_height) {
                        viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
                }
                else {
                        viewDir = normalize(viewPos - fs_in.FragPos);
                }

                vec2 texCoords;
                if (has_texture_height) {
//                        texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
                        texCoords = ParallaxMapping2(fs_in.TexCoords, viewDir);
                        //                if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
                        //                        discard;
                }
                else {
                        texCoords = fs_in.TexCoords;
                }

                if (has_texture_opacity) {

                        float opacity = texture2D(texture_opacity, texCoords).r;
                        if (opacity < 0.1) {
                                discard;
                        }
                }

                //    FragColor = vec4(dirLight[0].ambient * vec3(texture2D(texture_diffuse1, fs_in.TexCoords)), 1.0);
                //    return;


                //    vec4 texColor = texture2D(texture_diffuse1, fs_in.TexCoords);
                //    if (texColor.a < 0.1)
                //        discard;
                //    FragColor = texColor;

                // properties
                vec3 normal;
                //                vec3 viewDir;
                if (has_texture_normal) {
                        //             vec2 tex = fs_in.TexCoords;
                        //             tex.y = 1 -tex.y;
                        normal = texture2D(texture_normal, texCoords).rgb;
                        //                        normal = texture2D(texture_normal, fs_in.TexCoords).rgb;
                        normal = normalize(normal * 2.0 - 1.0);
                        //                        normal = normalize(fs_in.TBN * normal);

                        //                normal.g = -normal.g;
                        //                        viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
                }
                else {
                        normal = normalize(fs_in.Normal);
                        //                        viewDir = normalize(viewPos - fs_in.FragPos);
                }
                //        vec3 normal = normalize(fs_in.Normal);

                //    FragColor = vec4(viewDir, 1.0);
                //    return;
                // == =====================================================
                // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
                // For each phase, a calculate function is defined that calculates the corresponding color
                // per lamp. In the main() function we take all the calculated colors and sum them up for
                // this fragment's final color.
                // == =====================================================
                // phase 1: directional lighting
                for (int i =0; i <nbDirLight; ++i) {
                        result += CalcDirLight(dirLight[i], normal, viewDir, texCoords);
                }
                //    result /= nbDirLight;
                //            result += CalcDirLight(dirLight[0], norm, viewDir);
                // phase 2: point lights
                //    for(int i = 0; i < NR_POINT_LIGHTS; i++)
                for(int i = 0; i < nbPointLight; i++) {
                        //                    if (pointLights[i].computed)
                        vec3 lightDir;
                        if (has_texture_normal || has_texture_height) {
                                //                        if (has_texture_normal) {
                                lightDir = normalize(fs_in.TangentLightPos[i] - fs_in.TangentFragPos);
                        }
                        else {
                                lightDir = normalize(pointLights[i].position - fs_in.FragPos);
                        }

                        result += CalcPointLight(pointLights[i], normal, fs_in.FragPos, viewDir, lightDir, texCoords);
                }
                //    // phase 3: spot light
                for(int i =0; i <nbSpotLight; ++i) {
                        vec3 lightDir;
                        //                        if (has_texture_normal || has_texture_height) {
                        if (has_texture_normal) {
                                lightDir = normalize(fs_in.TangentLightPos[i + nbPointLight] - fs_in.TangentFragPos);
                        }
                        else {
                                lightDir = normalize(spotLights[i].position - fs_in.FragPos);

                        }
                        result += CalcSpotLight(spotLights[i], normal, fs_in.FragPos, viewDir, lightDir, texCoords, fs_in.TangentLightDir[i]);
                }

        }
        //    if (length(result) < 0.01) {
        //        discard;
        //    }
        //        float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
        //        vec3 v = result *  vec3(0.2126, 0.7152, 0.0722);
        //        if(brightness > 1.0)
        //        if (v.r > 1.0 || v.g > 1.0 || v.b > 1.0)
        if (result.r > 1.0 || result.g > 1.0 || result.b > 1.0)
                BrightColor = vec4(result, 1.0);
        //                BrightColor = vec4(1.0, 0.0, 0.0, 1.0);
        else
                BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

        FragColor = vec4(result, 1.0);
        //        BrightColor = vec4(1.0, 1.0, 0.0, 1.0);
        //    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

// --------- CALCULATE LIGHT CONTRIBUTION
// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec2 texCoords)
{
        vec3 lightDir;
        //        if (has_texture_normal) {
        //            lightDir = normalize(TangentLightPos[light.id] - TangentFragPos);
        //        }
        //        else {
        lightDir = normalize(-light.direction);
        //        }
        // diffuse shading
        //        if (dot(lightDir, -viewDir) > 0.9) {
        //            return vec3(1.0);
        //        }

        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        //            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
        //        vec3
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // combine results
        vec3 ambient;
        vec3 diffuse;
        //        vec3 specular;
        if (has_texture_diffuse) {
                vec4 texColor = texture2D(texture_diffuse, texCoords);
                if (texColor.a < 0.5)
                        discard;

                if (length(vec3(texColor)) < 0.01) // uv texture failed
                        discard;

                ambient = light.ambient * vec3(texColor);
                //            diffuse = light.diffuse * diff * vec3(texColor);
                diffuse = light.diffuse * diff * vec3(texColor);
                //            diffuse = light.diffuse * diff * material.diffuse;
                //            ambient = vec3(diff);
                //                specular = light.specular * vec3(texColor);
        }
        else {
                ambient = light.ambient * material.ambient;
                //            ambient = vec3(1.0, 0.0, 0.0);

                diffuse = light.diffuse * diff * material.diffuse;
                //            diffuse = material.diffuse;
                //            diffuse = vec3(1.0, 0.0, 0.0);
        }

        //    diffuse = light.diffuse * diff * material.diffuse;
        //    vec3 specular = light.specular * spec * vec3(texture2D(texture_specular1, fs_in.TexCoords));
        //        vec3 specular = light.specular * spec * max(vec3(0.1), material.specular);
        vec3 specular;
        if (has_texture_specular) {
                specular = light.specular * spec * vec3(texture2D(texture_specular, texCoords)).r;
        }
        else {
                specular = light.specular * spec * material.specular;
                //                specular = glm::vec3(0.0, 1.0, 0.0);
        }
        //            vec3 specular = light.specular * spec * vec3(0.2, 0.2, 0.1);
        //            vec3 specular = light.specular * spec * vec3(1.0f);
        //    vec3 specular = light.specular * spec * vec3(0.1, 0.1, 0.1);
        //    return ambient;
        //    return diffuse;
        //    return specular;
        if (shadow) {
                float shadow = ShadowCalculation(fs_in.FragPosLightSpace[light.id], normal, light);
                return (ambient + (1.0 - shadow) * (diffuse + specular));
        } else {

                return ambient + diffuse + specular;
        }
        //    return vec3(0.0, 1.0, 0.0);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 lightDir, vec2 texCoords, vec3 lightDir2)
{
//	lightDir = normalize(fs_in.TangentLightPos[i + nbPointLight] - fs_in.TangentFragPos);
//	lightDir = normalize(spotLights[i].position - fs_in.FragPos);

//                vec3 lightDir = normalize(light.position - fragPos);
//        lightDir = normalize(-light.direction);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2.0f);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // spotlight intensity
//        float theta = dot(lightDir, normalize(-light.direction));
        float theta = dot(lightDir, normalize(lightDir2));
//        float theta = 1.0;
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        //    vec3 ambient = light.ambient * vec3(texture2D(texture_diffuse1, fs_in.TexCoords));
        //    vec3 diffuse = light.diffuse * diff * vec3(texture2D(texture_diffuse1, fs_in.TexCoords));
        //    vec3 specular = light.specular * spec * vec3(texture2D(texture_specular1, fs_in.TexCoords));
        vec3 ambient;
        vec3 diffuse;
        if (has_texture_diffuse) {
                vec4 texColor = texture2D(texture_diffuse, texCoords);
                if (texColor.a < 0.5)
                        discard;

                if (length(vec3(texColor)) < 0.01) // uv texture failed
                        discard;

                ambient = light.ambient * vec3(texColor);
                //            diffuse = light.diffuse * diff * vec3(texColor);
                diffuse = light.diffuse * diff * vec3(texColor);
                //            diffuse = light.diffuse * diff * material.diffuse;
                //            ambient = vec3(diff);
        }
        else {
                ambient = light.ambient * material.ambient;
                //            ambient = vec3(1.0, 0.0, 0.0);

                diffuse = light.diffuse * diff * material.diffuse;
                //            diffuse = material.diffuse;
                //            diffuse = vec3(1.0, 0.0, 0.0);
        }

        //    diffuse = light.diffuse * diff * material.diffuse;
        //    vec3 specular = light.specular * spec * vec3(texture2D(texture_specular1, fs_in.TexCoords));

        //        vec3 specular = light.specular * spec * material.specular;
        vec3 specular;
        if (has_texture_specular) {
                specular = light.specular * spec * vec3(texture2D(texture_specular, texCoords)).r;
        }
        else {
                specular = light.specular * spec * material.specular;
        }
        //    vec3 specular = light.specular * spec * vec3(0.2, 0.2, 0.1);
        //    vec3 specular = light.specular * spec * vec3(0.1, 0.1, 0.1);
        //    return ambient;
        //    return diffuse;
        //    return specular;
        //    return ambient + diffuse + specular;
        if (shadow) {
                float shadow = ShadowCalculation(fs_in.FragPosLightSpace[light.id], normal, light);
                ambient *= attenuation * intensity;
                diffuse *= attenuation * intensity;
                specular *= attenuation * intensity;

                return (ambient + (1.0 - shadow) * (diffuse + specular));
        }
        else {
                return (ambient + diffuse + specular);
        }
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 lightDir, vec2 texCoords)
{
        //        vec3 lightDir;
        //        if (has_texture_normal) {
        //            lightDir = normalize(TangentLightPos[light.id] - TangentFragPos);
        //        }
        //        else {
        //        lightDir = normalize(-light.direction);
        //        lightDir = normalize(light.position - fragPos);
        //        }
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        //        vec3 halfwayDir = normalize(lightDir + viewDir);
        //        float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // combine results
        vec3 ambient;
        vec3 diffuse;
        if (has_texture_diffuse) {
                vec4 texColor = texture2D(texture_diffuse, texCoords);
                if (texColor.a < 0.5)
                        discard;

                if (length(vec3(texColor)) < 0.01) // uv texture failed
                        discard;
                //            if (length(texColor) < 0.1)
                ambient = light.ambient * vec3(texColor);
                diffuse = light.diffuse * diff * vec3(texColor);
        }
        else {
                ambient = light.ambient * material.ambient;
                diffuse = light.diffuse * diff * material.diffuse;
        }

        //    diffuse = light.diffuse * diff * material.diffuse;
        //    vec3 specular = light.specular * spec * vec3(texture2D(texture_specular1, fs_in.TexCoords));
        //        vec3 specular = light.specular * spec * material.specular;
        vec3 specular;
        if (has_texture_specular) {
                specular = light.specular * spec * vec3(texture2D(texture_specular, texCoords)).r;
                //                specular = light.specular;
                //                specular = vec3(texture2D(texture_specular, fs_in.TexCoords));
        }
        else {
                specular = light.specular * spec * material.specular;
                //                specular = material.specular;
                //                specular = spec;
        }
        //            vec3 specular = light.specular * spec * vec3(1.0);

        //    vec3 ambient = light.ambient * vec3(texture2D(texture_diffuse1, fs_in.TexCoords));
        //    vec3 diffuse = light.diffuse * diff * vec3(texture2D(texture_diffuse1, fs_in.TexCoords));
        //    vec3 specular = light.specular * spec * vec3(texture2D(texture_specular1, fs_in.TexCoords));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        //    float shadow = ShadowCalculation(vec3(fs_in.FragPosLightSpace[light.id]), light);
        if (shadow) {
                float shadow = ShadowCalculation(fs_in.FragPos, normal, light);
                return (ambient + (1.0 - shadow) * (diffuse + specular));
        } else {
                return (ambient + diffuse + specular);

        }

        //    return vec3(1.0, 1.0, 1.0);
}

// ----------------------------- SHADOW CALCULATION
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, DirLight light)
{
        // perform perspective divide
        vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
        //    float closestDepth = texture(shadowMap, projCoords.xy).r;
        //    float closestDepth = texture(light.shadowMap, projCoords.xy).r;
        // get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;
        // check whether current frag pos is in shadow

//        float bias = 0.001;
        float bias = light.bias;
        //    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
        //    return currentDepth -bias  > closestDepth  ? 1.0 : 0.0;
        //    float shadow = currentDepth -bias > closestDepth  ? 1.0 : 0.0;
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(light.shadowMap, 0);
        //        float dist = length(fs_in.FragPos - )
        int size = 2;
        for(int x = -size; x <= size; ++x)
        {
                for(int y = -size; y <= size; ++y)
                {
                        float pcfDepth = texture(light.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                        shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
                }
        }
        int area = size * 2 +1;
        area = area * area;
        shadow /= area;

        //    float shadow  = 0.0;
        //    float bias    = 0.5;
        //    float samples = 4.0;
        //    float offset  = 0.5;
        //    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
        //    {
        //        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        //        {
        ////            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
        ////            {
        //                float closestDepth = texture(light.shadowMap, projCoords.xy + vec2(x, y)).r;
        //                closestDepth *= far_plane;   // Undo mapping [0;1]
        //                if(currentDepth - bias > closestDepth)
        //                    shadow += 1.0;
        ////            }
        //        }
        //    }
        //    shadow /= (samples * samples);

        if (projCoords.z > 1.0)
                shadow = 0.0;

        return shadow;
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, SpotLight light)
{
        // perform perspective divide
        vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
        //    float closestDepth = texture(shadowMap, projCoords.xy).r;
        //    float closestDepth = texture(light.shadowMap, projCoords.xy).r;
        // get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;
        // check whether current frag pos is in shadow

        //        float bias = 0.001;
//                float bias = light.bias;
//        float bias = max(0.01 * (1.0 - dot(normal, light.direction)), 0.001);
        float bias = max(light.bias * (1.0 - dot(normal, light.direction)), 0.001);

        //    return currentDepth -bias  > closestDepth  ? 1.0 : 0.0;
        //    float shadow = currentDepth -bias > closestDepth  ? 1.0 : 0.0;
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(light.shadowMap, 0);
        int size = 1;
        for(int x = -size; x <= size; ++x)
        {
                for(int y = -size; y <= size; ++y)
                {
                        float pcfDepth = texture(light.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                        shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
                }
        }
        int area = size * 2 +1;
        area = area * area;
        shadow /= area;

        //    float shadow  = 0.0;
        //    float bias    = 0.5;
        //    float samples = 4.0;
        //    float offset  = 0.5;
        //    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
        //    {
        //        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        //        {
        ////            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
        ////            {
        //                float closestDepth = texture(light.shadowMap, projCoords.xy + vec2(x, y)).r;
        //                closestDepth *= far_plane;   // Undo mapping [0;1]
        //                if(currentDepth - bias > closestDepth)
        //                    shadow += 1.0;
        ////            }
        //        }
        //    }
        //    shadow /= (samples * samples);

        if (projCoords.z > 1.0)
                shadow = 0.0;

        return shadow;
}

float ShadowCalculation(vec3 fragPos, vec3 normal, PointLight light)
{
        // get vector between fragment position and light position
        vec3 fragToLight = fragPos - light.position;
        // ise the fragment to light vector to sample from the depth map

        //    float closestDepth = texture(light.shadowMap, fragToLight).r;
        //    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
        //    closestDepth *= far_plane;
        //    // now get current linear depth as the length between the fragment and light position
        float currentDepth = length(fragToLight);
        //    // test for shadows
        //    float bias = 0.5; // we use a much larger bias since depth is now in [near_plane, far_plane] range
        //    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

        //    float bias = max(0.5 * (1.0 - dot(normal, normalize(fragToLight))), 0.005);
        //    float bias = 0.001; // we use a much larger bias since depth is now in [near_plane, far_plane] range

        // display closestDepth as debug (to visualize depth cubemap)
        // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);

        //            float shadow  = 0.0;
        //            float bias    = 10.0;
        //            float samples = 4.0;
        //            float offset  = 0.5;
        //            for(float x = -offset; x < offset; x += offset / (samples * 0.5))
        //            {
        //                for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        //                {
        //                    for(float z = -offset; z < offset; z += offset / (samples * 0.5))
        //                    {
        //                        float closestDepth = texture(light.shadowMap, fragToLight + vec3(x, y, z)).r;
        //                        closestDepth *= far_plane;   // Undo mapping [0;1]
        //                        if(currentDepth - bias > closestDepth)
        //                            shadow += 1.0;
        //                    }
        //                }
        //            }
        //            shadow /= (samples * samples * samples);
        //            return shadow;

        float shadow = 0.0;
//        float bias = 10.0;
        float bias = light.bias;
//            float bias = max(light.bias * (1.0 - dot(normal, normalize(fragToLight))), 0.005);
        int samples = 20;
        float viewDistance = length(viewPos - fragPos);
        float diskRadius = (1.0 + (viewDistance / far_plane)) / 2.0;
        //        float diskRadius = 0.5;
        for(int i = 0; i < samples; ++i)
        {
                float closestDepth = texture(light.shadowMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
                closestDepth *= far_plane;   // undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                        shadow += 1.0;
        }
        shadow /= float(samples);

        return shadow;
}
