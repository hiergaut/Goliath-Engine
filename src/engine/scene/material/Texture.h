#ifndef TEXTURE_H
#define TEXTURE_H

#include <QPixmap>
#include <iostream>
#include <opengl/version.h>
#include <vector>

//struct Texture;
class Texture;
using Textures = std::vector<Texture>;

class Texture {
public:
    unsigned int m_id;
    //    std::string type;
    enum Type {
        DIFFUSE = 0,
        SPECULAR,
        NORMAL,
        HEIGHT,
        size
    } m_type;

    std::string m_directory;
    std::string m_filename;

    QPixmap m_pixmap;

    Texture(std::string path, std::string filename, Texture::Type type);
    //    Texture(const Texture & texture);
    Texture(Texture&& texture) = default;
    ~Texture();

    unsigned int TextureFromFile(const char* path, const std::string& directory);

    operator const char*() const;

private:
    QOpenGLFunctionsCore* m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
};

#endif // TEXTURE_H
