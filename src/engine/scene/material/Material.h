#ifndef MATERIAL_H
#define MATERIAL_H

#include <QPixmap>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <opengl/version.h>
#include "Color.h"
#include "Texture.h"

class Material;
using Materials = std::vector<Material>;


class Material {
public:

    std::vector<uint> m_iTextures[Texture::size];

    std::string m_name;
    Color m_colors[Color::Etype::size];
    //    glm::vec3 m_colorDiffuse;
    //    glm::vec3 m_colorSpecular;
    //    glm::vec3 m_colorAmbient;
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
    Material(const aiMaterial * ai_material, Textures & textures, std::string directory);
    std::vector<uint> assimpLoadMaterialTextures(const aiMaterial* mat, aiTextureType ai_type, Texture::Type type);
unsigned int TextureFromFile(const char* path, const std::string& directory);

private:
    std::string m_directory;
    Textures & m_textures;
    QOpenGLFunctionsCore * m_fun;
};

#endif // MATERIAL_H