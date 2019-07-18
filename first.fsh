#version 330 core
//out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    FragColor = vec4(ourColor, 1.0f);
//    gl_FragColor = texture2D(texture1, TexCoord);
//    gl_FragColor = texture2D(texture1, TexCoord) * vec4(ourColor, 1.0);
    gl_FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, vec2(TexCoord.x, 1 -TexCoord.y)), 0.2);
};
