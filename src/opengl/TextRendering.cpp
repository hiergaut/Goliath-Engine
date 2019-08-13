#include "TextRendering.h"

TextRendering::TextRendering()
{
}

void TextRendering::initialize()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    // Init GLFW
    // Define the viewport dimensions
    //        glViewport(0, 0, WIDTH, HEIGHT);

    // Set OpenGL options
    // Compile and setup the shader
    //        Shader shader("text.vsh", "text.fsh");
            glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(500), 0.0f, static_cast<GLfloat>(500));
    m_shader = new Shader ("text.vsh", "text.fsh");
    m_shader->use();
//            m_fun->glUniformMatrix4fv(m_fun->glGetUniformLocation(m_shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            m_shader->setMat4("projection", projection);

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    FT_Face face;
    std::string fontFile = "Ubuntu.ttf";
//    std::string fontFile = "LiberationMono-Regular.ttf";
    if (FT_New_Face(ft, (g_resourcesPath + "fonts/" + fontFile).c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    m_fun->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        m_fun->glGenTextures(1, &texture);
        m_fun->glBindTexture(GL_TEXTURE_2D, texture);
        m_fun->glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // Set texture options
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<uint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    m_fun->glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    m_fun->glGenVertexArrays(1, &VAO);
    m_fun->glGenBuffers(1, &VBO);
    m_fun->glBindVertexArray(VAO);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    m_fun->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_fun->glBindVertexArray(0);

    // Game loop

    // Clear the colorbuffer
    //            RenderText(shader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    //            RenderText(shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

    // Swap the buffers
    //            glfwSwapBuffers(window);
    //        }

    //        glfwTerminate();
    //        return 0;

}

void TextRendering::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Activate corresponding render state
    //        shader.Use();
    m_shader->use();
    m_fun->glUniform3f(m_fun->glGetUniformLocation(m_shader->ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    m_fun->glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos, ypos, 0.0, 1.0 },
            { xpos + w, ypos, 1.0, 1.0 },

            { xpos, ypos + h, 0.0, 0.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 }
        };
        // Render glyph texture over quad
        m_fun->glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        m_fun->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        m_fun->glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        m_fun->glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    m_fun->glBindVertexArray(0);
    m_fun->glBindTexture(GL_TEXTURE_2D, 0);
}
