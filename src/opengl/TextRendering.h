#ifndef TEXTRENDERING_H
#define TEXTRENDERING_H

// Std. Includes
#include <iostream>
#include <map>
#include <string>
// GLEW
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#include <opengl/shader.h>
#include <opengl/version.h>

// Properties
//const GLuint WIDTH = 800, HEIGHT = 600;
namespace {
struct Character {
    GLuint TextureID; // ID handle of the glyph texture
    glm::ivec2 Size; // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance; // Horizontal offset to advance to next glyph
};
}

class TextRendering {
    /// Holds all state information relevant to a character as loaded using FreeType
public:
    TextRendering();
    void initialize();
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
    QOpenGLFunctionsCore* m_fun;
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
    Shader * m_shader;

    // The MAIN function, from here we start our application and run the Game loop
};

#endif // TEXTRENDERING_H
