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
    enum Type {
        DIFFUSE = 0,
        SPECULAR,
        NORMAL,
        HEIGHT,
        OPACITY,
        size
    } m_type;

    static const char* to_string(Type type)
    {
        switch (type) {
        case DIFFUSE:
            return "diffuse";

        case SPECULAR:
            return "specular";

        case NORMAL:
            return "normal";

        case HEIGHT:
            return "height";

        default:
            throw std::out_of_range("no texture type");
        }
    }

public:
    Texture(std::string path, std::string filename, Texture::Type type);
    Texture(std::ifstream& file);

    Texture(const Texture& texture) = delete;
    Texture(Texture&& texture) = default;
    ~Texture();

    void save(std::ofstream& file) const;

    unsigned int TextureFromFile(const char* path, const std::string& directory);

    operator const char*() const;

private:
    QOpenGLFunctionsCore* m_fun;

    //    Type m_type;
    //    std::string type;
};

#endif // TEXTURE_H
