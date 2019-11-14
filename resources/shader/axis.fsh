#version 330 core
out vec4 FragColor;


in vec3 Position;

void main()
{    
    float alpha = 1.0f;
    if (Position.x > 0) {
        FragColor = vec4(1.0f, 0, 0, alpha);
    }
    else if (Position.y > 0) {
        FragColor = vec4(0.0, 1.0, 0.0, alpha);
    }
    else if (Position.z > 0) {
        FragColor = vec4(0.0, 0.0, 1.0, alpha);
    }
}
