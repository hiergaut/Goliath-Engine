#version 330 core
out vec4 FragColor;


in vec3 Position;

void main()
{    
    float alpha = 0.8f;
//    if (Position.x = 0) {
//        FragColor = vec4(0.0, 1.0, 0.0, alpha);
//    }
//    else if (Position.y = 0) {
//        FragColor = vec4(1.0, 0.0, 0.0, alpha);
//    }
//    else {
//        discard;
//    }

    if (Position.x >= 0 && Position.y >= 0) {
            if (Position.y == 0) {
                    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
            else if (Position.x == 0) {
                    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
                    //            FragColor = vec4(0.8, 0.8, 0.8, 0.5);
            }
            else {
                    FragColor = vec4(0.8, 0.8, 0.8, alpha);
            }
    }
    else {
            FragColor = vec4(0.8, 0.8, 0.8, alpha);
    }
}
