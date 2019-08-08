#include "Material.h"

//#include "Assimp.h"
#include <assimp/Assimp.h>

//Material::Material(std::string name) : m_name(name)
//{
//    for (int i =0; i <Color::Etype::size; ++i) {
//        m_colors[i].type = static_cast<Color::Etype>(i);
//    }
//#include "stb_image.h"
//#include <image/tga.h>
//#include <fstream>

Material::Material(const aiMaterial* ai_material, Textures& textures, std::string directory)
     : m_directory(directory),
     m_textures(textures)
//      m_fun(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>())
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    for (int i =0; i <Color::Etype::size; ++i) {
        m_colors[i].type = static_cast<Color::Etype>(i);
    }

    aiString ai_name;
    ai_material->Get(AI_MATKEY_NAME, ai_name);
    //        Material material(ai_name.C_Str());
    m_name = ai_name.C_Str();
    //        qDebug() << ai_name.C_Str();
    aiColor3D ai_ambient;
    ai_material->Get(AI_MATKEY_COLOR_AMBIENT, ai_ambient);
    m_colors[0] = aiColor3ToGlm(ai_ambient);

    aiColor3D ai_diffuse;
    ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_diffuse);
    //        qDebug() << ai_diffuse.b << ai_diffuse.g << ai_diffuse.r;
    m_colors[1] = aiColor3ToGlm(ai_diffuse);

    aiColor3D ai_specular;
    ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_specular);
    m_colors[2] = aiColor3ToGlm(ai_specular);

    //        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;
    //        float ai_shininess;
    ai_material->Get(AI_MATKEY_SHININESS, m_shininess);
    //        material.m_shininess = ai_shininess;
    //        aiColor3D ai_emissive;
    //        aiColor3D ai_transparent;

    // 1. diffuse maps
    //        std::vector<uint> textures;
    m_iTextures[Texture::DIFFUSE] = assimpLoadMaterialTextures(ai_material, aiTextureType_DIFFUSE, Texture::DIFFUSE);
    //        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    m_iTextures[Texture::SPECULAR] = assimpLoadMaterialTextures(ai_material, aiTextureType_SPECULAR, Texture::SPECULAR);
    //        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    m_iTextures[Texture::NORMAL] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::NORMAL);
    //        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    m_iTextures[Texture::HEIGHT] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::HEIGHT);
    //        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


//    std::cout << "\033[32m";
//    std::cout << "[Material] " << m_name << " created " << this << std::endl;
////    std::cout << "m_textures : " << m_colors << std::endl;
//    std::cout << "\033[0m";
}

//Material::Material(const Material && material) : m_textures(material.m_textures)
//{
////    m_textures = material.m_textures;
//    std::cout << "\033[34m";
//    std::cout << "[Material] " << m_name << " " << &material << "right moving to " << this << std::endl;
//    std::cout << "m_textures : " << m_colors << std::endl;
//    std::cout << "\033[0m";
//}

//Material::Material(const Material & material) : m_textures(material.m_textures)
//{
//    std::cout << "\033[35m";
//    std::cout << "[Material] " << m_name << " " << &material << " left moving to " << this << std::endl;
////    std::cout << "m_textures : " << m_colors << std::endl;
//    std::cout << "\033[0m";

//}

Material::~Material()
{
    std::cout << "\033[31m";
    std::cout << "[Material] " << m_name << " destruct " << this << std::endl;
//    std::cout << "m_textures : " << m_colors << std::endl;
    std::cout << "\033[0m";
}


//}
//    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false)


std::vector<uint> Material::assimpLoadMaterialTextures(const aiMaterial* mat, aiTextureType ai_type, Texture::Type type)
{
    //    std::vector<Texture> textures;
    std::vector<uint> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(ai_type); i++) {
        //        qDebug() << "has textures";
        aiString ai_filename;
        mat->GetTexture(ai_type, i, &ai_filename);
        std::string filename(ai_filename.C_Str());
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < m_textures.size(); j++) {
            if (std::strcmp(m_textures[j].m_directory.data(), filename.c_str()) == 0) {
                //                textures.push_back(m_textures[j]);
                textures.push_back(j);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip) { // if texture hasn't been loaded already, load it
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), m_directory);
//            texture.type = type;
//            texture.m_directory = m_directory + "/" + str.C_Str();
//            texture.m_filename = str.C_Str();
//            bool success;
//            QImage image = loadTga(texture.m_directory.c_str(), success);
//            Q_ASSERT(success);
//            //            Q_ASSERT(! image.isNull());
//            //            QPixmap pixmap(image);
//            //            QPixmap pixmap(QPixmap::fromImage(image));
//            texture.pixmap = QPixmap::fromImage(image);
            //            textures.push_back(texture);
            textures.push_back(m_textures.size());
//            m_textures.push_back(std::move(texture)); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//            Texture texture(m_directory, filename, type);

            m_textures.emplace_back(m_directory, filename, type);
        }
    }
    return textures;
}
