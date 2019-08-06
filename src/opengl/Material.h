#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <vector>
#include <QPixmap>
#include <glm/glm.hpp>

struct Texture {
    unsigned int id;
    //    std::string type;
    enum e_type {
        diffuse = 0,
        specular,
        normal,
        height,
        size
    } type;

    std::string path;

    QPixmap pixmap;

    operator const char*() const
    {
        switch (type) {
        case e_type::diffuse:
            return "diffuse";

        case e_type::specular:
            return "specular";

        case e_type::normal:
            return "normal";

        case e_type::height:
            return "height";

        default:
            throw std::out_of_range("no texture type");
        }
    }
};

class Material {
public:
    std::vector<uint> m_textures[Texture::e_type::size];

    std::string m_name;
    glm::vec3 m_colorDiffuse;
    glm::vec3 m_colorSpecular;
    glm::vec3 m_colorAmbient;
    float m_shininess;
    //    std::vector<uint> m_diffuseMaps;
    //    std::vector<uint> m_specularMaps;
    //    std::vector<uint> m_normalMaps;
    //    std::vector<uint> m_heightMaps;

    //    uint m_diffuseMap;
    //    uint m_specularMap;
    //    uint m_normalMap;
    //    uint m_heightMap;

public:
    Material(std::string name);
};

#endif // MATERIAL_H
