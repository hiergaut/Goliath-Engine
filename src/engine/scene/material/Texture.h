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
    QPixmap m_pixmap;
    std::string m_filename;
    std::string m_directory;

public:
    enum Type {
        DIFFUSE = 0,
        SPECULAR,
        NORMAL,
        HEIGHT,
        size
    };

    Texture(std::string path, std::string filename, Texture::Type type);
    //    Texture(const Texture & texture);
    Texture(Texture&& texture) = default;
    ~Texture();

    unsigned int TextureFromFile(const char* path, const std::string& directory);

    operator const char*() const;

private:
    QOpenGLFunctionsCore* m_fun;

    Type m_type;
    //    std::string type;


};

#endif // TEXTURE_H
