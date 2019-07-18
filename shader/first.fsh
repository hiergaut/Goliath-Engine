#version 330 core
//out vec4 FragColor;

//in vec3 ourColor;
in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
//        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    FragColor = vec4(ourColor, 1.0f);
//    gl_FragColor = texture2D(texture1, TexCoord);
//    gl_FragColor = texture2D(texture1, TexCoord) * vec4(ourColor, 1.0);
    vec3 objectColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, vec2(TexCoord.x, 1 -TexCoord.y)), 0.2).xyz;
//    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;



//    vec3 result = ambient * objectColor;
//    vec3 result = diffuse * objectColor;
//    vec3 result = specular * objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    gl_FragColor = vec4(result, 1.0);
}
