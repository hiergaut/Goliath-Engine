#include "Texture.h"

//Texture::Texture()
//{

//}
#include <assimp/scene.h>
#include <image/stb_image.h>
#include <image/tga.h>

#include <QDebug>
#include <session/Session.h>

//unsigned int TextureFromFile(const std::string& filename, const std::string& directory);

Texture::Texture(std::string path, std::string filename, Texture::Type type)
    : m_filename(filename)
    , m_directory(path)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    std::cout << "\033[32m";
    //    std::cout << "[Texture] " << m_filename << " created " << this << std::endl;
    //    std::cout << "\033[0m";
    //            Texture texture;
    m_type = type;
    m_id = TextureFromFile(filename.c_str(), m_directory);
    if (m_type == Texture::Type::NORMAL) {
        qDebug() << m_filename.c_str() << "normal";
    }
    //            m_directory = m_directory + "/" + str.C_Str();
    //            texture.m_filename = str.C_Str();
    bool success;
    QImage image = loadTga(m_directory + "/" + m_filename, success);
    //    Q_ASSERT(success);

    //            Q_ASSERT(! image.isNull());
    //            QPixmap pixmap(image);
    //            QPixmap pixmap(QPixmap::fromImage(image));

    m_pixmap = QPixmap::fromImage(image);

    //            textures.push_back(texture);
    //            textures.push_back(m_textures.size());
    //            m_textures.push_back(std::move(texture)); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
}

Texture::Texture(std::ifstream& file)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    Session::load(m_id, file);
    Session::load(m_filename, file);
    Session::load(m_directory, file);

    m_type = Texture::Type(Session::loadEnum(file));
    m_id = TextureFromFile(m_filename.c_str(), m_directory);


    bool success;
    QImage image = loadTga(m_directory + "/" + m_filename, success);
    //    Q_ASSERT(success);
    //            Q_ASSERT(! image.isNull());
    //            QPixmap pixmap(image);
    //            QPixmap pixmap(QPixmap::fromImage(image));
    if (success)
        m_pixmap = QPixmap::fromImage(image);
    //            textures.push_back(texture);
}

//Texture::Texture(const Texture &texture)
//{
//    std::cout << "\033[31m";
//    std::cout << "[TEXTURE] '" << m_filename << "' copy constructor " << this << std::endl;
//    std::cout << "\033[0m";
//}

//Texture::Texture(const Texture &texture)
//{
//    std::cout << "[Texture] '" << m_filename << "' fuck " << this << std::endl;

//}

Texture::~Texture()
{

    std::cout << "\033[35m";
    std::cout << "[Texture] '" << m_filename << "' deleted " << this << std::endl;
    std::cout << "\033[0m";
}

void Texture::save(std::ofstream& file) const
{
    //    Session::save(m_id, file);
    Session::save(m_filename, file);
    Session::save(m_directory, file);
    Session::saveEnum(static_cast<int>(m_type), file);

    //    bool success;
    //    QImage image = loadTga(m_directory +"/" + m_filename, success);
    //    Q_ASSERT(success);
    //            Q_ASSERT(! image.isNull());
    //            QPixmap pixmap(image);
    //            QPixmap pixmap(QPixmap::fromImage(image));
    //    m_pixmap = QPixmap::fromImage(image);
    //            textures.push_back(texture);
}

Texture::operator const char*() const
{
    switch (m_type) {
    case DIFFUSE:
        return "diffuse";

    case SPECULAR:
        return "specular";

    case NORMAL:
        return "normal";

    case HEIGHT:
        return "height";

    case OPACITY:
        return "opacity";

    default:
        throw std::out_of_range("no texture type");
    }
}

unsigned int Texture::TextureFromFile(const char* path, const std::string& directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    //        QOpenGLFunctionsCore* fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        qDebug() << "model.h : " << fun;
    //        QOpenGLFunctions * fun = QOpenGLContext::currentContext()->functions();

    unsigned int textureID;
    m_fun->glGenTextures(1, &textureID);

    int width, height, nrComponents;
    if (m_type == Texture::NORMAL) {
        stbi_set_flip_vertically_on_load(1);
    } else {
        stbi_set_flip_vertically_on_load(0);
    }
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        m_fun->glBindTexture(GL_TEXTURE_2D, textureID);
        m_fun->glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        m_fun->glGenerateMipmap(GL_TEXTURE_2D);

        if (nrComponents == 4) {
            m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        } else {
            m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        m_fun->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
