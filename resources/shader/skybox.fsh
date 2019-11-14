#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
//in vec3 FragPos;

uniform samplerCube skybox;
uniform bool debug = false;

uniform vec3 lightDir;
//uniform vec3 viewPos;

void main()
{    
    vec3 coord;
    if (debug) {
            coord = vec3(TexCoords.x, TexCoords.y, TexCoords.z);
    }
    else {
            coord = vec3(TexCoords.x, TexCoords.z, TexCoords.y);
    }

        vec3 viewDir = normalize(TexCoords);

        float diff = dot(viewDir, normalize(-lightDir));
        float radius = 0.9999;
        if (diff > radius) {
//            float a = (diff - radius) * 500;
//            float b = (diff - radius) * 50;
//            FragColor = vec4(1.0, 0.8 + b, a, 1.0) * 10;
//            FragColor = vec4(1.0, 0.8, 0.0, 1.0) * 10.0 * dot(normalize(lightDir), vec3(0.0, 0.0, -1.0));
            FragColor = vec4(1.0, 0.8, 0.0, 1.0) * 10.0;
            return;
        }


//    vec3 coord = vec3(TexCoords.x, TexCoords.z, TexCoords.y);
//    FragColor = texture(skybox, TexCoords);
    FragColor = texture(skybox, coord);
}
