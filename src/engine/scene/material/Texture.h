#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <iostream>
#include <QPixmap>

struct Texture;
using Textures = std::vector<Texture>;

struct Texture {
    unsigned int id;
    //    std::string type;
    enum Type {
        DIFFUSE = 0,
        SPECULAR,
        NORMAL,
        HEIGHT,
        size
    } type;

    std::string directory;
    std::string filename;

    QPixmap pixmap;



    operator const char*() const
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
};


#endif // TEXTURE_H
