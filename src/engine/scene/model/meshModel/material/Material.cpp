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
#include <QPainter>
#include <fstream>

Material::Material(const aiMaterial* ai_material, Textures* textures, std::string directory)
    : m_textures(textures)
    , m_directory(directory)
//      m_fun(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>())
{
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    for (int i = 0; i < Color::Etype::size; ++i) {
        m_colors[i].type = static_cast<Color::Etype>(i);
    }

    aiString ai_name;
    ai_material->Get(AI_MATKEY_NAME, ai_name);
    //        Material material(ai_name.C_Str());
    m_name = ai_name.C_Str();
    //        qDebug() << ai_name.C_Str();
    aiColor3D ai_ambient;
    ai_material->Get(AI_MATKEY_COLOR_AMBIENT, ai_ambient);
    m_colors[Color::Etype::AMBIENT] = aiColor3ToGlm(ai_ambient);

    aiColor3D ai_diffuse;
    ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_diffuse);
    //        qDebug() << ai_diffuse.b << ai_diffuse.g << ai_diffuse.r;
    m_colors[Color::Etype::DIFFUSE] = aiColor3ToGlm(ai_diffuse);
//    std::cout << m_name << ": diffuse " << m_colors[Color::Etype::DIFFUSE].color.x << std::endl;


    aiColor3D ai_specular;
    ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_specular);
    m_colors[Color::Etype::SPECULAR] = aiColor3ToGlm(ai_specular);

    //        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;
    //        float ai_shininess;
    ai_material->Get(AI_MATKEY_SHININESS, m_shininess);
//    std::cout << m_name << ": shininess " << m_shininess << std::endl;
    m_shininess = std::max(1.0f, m_shininess);
    Q_ASSERT(m_shininess <= 256);
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
    m_iTextures[Texture::NORMAL] = assimpLoadMaterialTextures(ai_material, aiTextureType_NORMALS, Texture::NORMAL);
//    m_iTextures[Texture::NORMAL] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::NORMAL);
//    if (ai_material->GetTextureCount(aiTextureType_NORMALS) > 0) {
//        std::cout << m_name << ": normal texture loaded" << std::endl;
//    }
    //        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    m_iTextures[Texture::HEIGHT] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::HEIGHT);
    //        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    m_iTextures[Texture::OPACITY] = assimpLoadMaterialTextures(ai_material, aiTextureType_OPACITY, Texture::OPACITY);

    //    std::cout << "\033[32m";
    //    std::cout << "[Material] " << m_name << " created " << this << std::endl;
    ////    std::cout << "m_textures : " << m_colors << std::endl;
    //    std::cout << "\033[0m";
}

Material::Material(std::ifstream& file, Textures* textures)
    : m_textures(textures)
{
    //    uint size;
    for (uint i = 0; i < Texture::size; ++i) {
        //        std::cout << "m_iTextures[" << i << "]" << std::endl;
        Session::load(m_iTextures[i], file);
    }

    //    std::cout << "m_name" << std::endl;
    Session::load(m_name, file);

    for (uint i = 0; i < Color::size; ++i) {
        //        std::cout << "m_colors[" << i << "]" << std::endl;
        m_colors[i].load(file);
    }

    //    std::cout << "m_shininess" << std::endl;
    Session::load(m_shininess, file);
    //    std::cout << "m_directory" << std::endl;
    Session::load(m_directory, file);
}

Material::Material(std::string name, float shininess, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : m_shininess(shininess)
    , m_name(name)
//    , m_colors[Color::EType::AMBIENT] = ambient

{
    m_colors[Color::AMBIENT] = ambient;
    m_colors[Color::DIFFUSE] = diffuse;
    m_colors[Color::SPECULAR] = specular;
}

//Material::Material(Material &&material, Textures &textures)
//    : m_textures(textures)
//{

//}

//Material::Material(const Material & mat)
//    : m_textures(mat.m_textures)
//{
//    std::cout << "\033[31m";
//    std::cout << "[MATERIAL] " << m_name << " copy constructor " << this << std::endl;
//    std::cout << "\033[0m";
//}

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
    std::cout << "\033[35m";
    std::cout << "[Material] '" << m_name << "' deleted " << this << std::endl;
    //    std::cout << "m_textures : " << m_colors << std::endl;
    std::cout << "\033[0m";
}

glm::vec3& Material::ambient()
{
    return m_colors[Color::AMBIENT].color;
}

glm::vec3& Material::diffuse()
{
    return m_colors[Color::DIFFUSE].color;
}

glm::vec3& Material::specular()
{
    return m_colors[Color::SPECULAR].color;
}

void Material::save(std::ofstream& file) const
{
    for (uint i = 0; i < Texture::size; ++i) {
        //        std::cout << "m_iTextures[" << i << "]" << std::endl;
        Session::save(m_iTextures[i], file);
    }

    //    std::cout << "m_name" << std::endl;
    Session::save(m_name, file);

    for (uint i = 0; i < Color::size; ++i) {
        //        std::cout << "m_colors[" << i << "]" << std::endl;
        m_colors[i].save(file);
    }

    //    std::cout << "m_shininess" << std::endl;
    Session::save(m_shininess, file);
    //    std::cout << "m_directory" << std::endl;
    Session::save(m_directory, file);
}

void Material::buildItemModel(QStandardItem* parent) const
{
    QStandardItem* item2 = new QStandardItem(QIcon(":/icons/material.png"), m_name.c_str());

    QStandardItem* itemAmbient = new QStandardItem("ambient");
    item2->appendRow(itemAmbient);

    //    material.
    //    QPainter * paint = new QPainter(&pixmap);
    QPixmap pixmap(":/icons/disk.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    //    painter.fillRect(pixmap.rect(), Qt::red);
    for (int i = 0; i < Color::Etype::size; ++i) {
        const Color& color(m_colors[i]);
        //    for ()
        painter.fillRect(pixmap.rect(), color);
        //        painter.end();
        //    paint->setBrush(QBrush(Qt::black));
        //    paint->drawPie(pixmap.rect(), 0, 1);
        //    pixmap.fill(QColor(material.m_colorDiffuse.x * 255.0f, material.m_colorDiffuse.y * 255.0f, material.m_colorDiffuse.z * 255.0f));

        QIcon icon(pixmap);

        if (i == 0) {
            QStandardItem* item3 = new QStandardItem(icon, "");
            itemAmbient->appendRow(item3);
        } else {
            QStandardItem* item3 = new QStandardItem(icon, color.to_string());
            item2->appendRow(item3);
        }
    }
    painter.end();

    for (int i = 0; i < Texture::size; ++i) {
        for (int j = 0; j < m_iTextures[i].size(); ++j) {
            const Texture& texture = (*m_textures)[m_iTextures[i][j]];

            if (i == 0) {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.m_pixmap), texture.m_filename.c_str());
                itemAmbient->appendRow(item3);
            } else {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.m_pixmap), QString(texture) + ": " + texture.m_filename.c_str());
                item2->appendRow(item3);
            }
        }
    }
    QStandardItem* shininess = new QStandardItem("shininess: " + QString::number(m_shininess));
    item2->appendRow(shininess);
    parent->appendRow(item2);
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
        for (unsigned int j = 0; j < m_textures->size(); j++) {
            if (std::strcmp((*m_textures)[j].m_directory.data(), filename.c_str()) == 0) {
                //                textures.push_back(m_textures[j]);
                textures.push_back(j);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                std::cout << filename.c_str() << " already loaded";
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
            textures.push_back(m_textures->size());
            //            m_textures.push_back(std::move(texture)); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            //            Texture texture(m_directory, filename, type);

            m_textures->emplace_back(m_directory, filename, type);
        }
    }
    Q_ASSERT(textures.size() <= 1);
    return textures;
}
