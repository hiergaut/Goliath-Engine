#ifndef MODEL_H
#define MODEL_H

//#include <glad/glad.h>
#include "version.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"
//#include <QOpenGLContext>

#include "mesh.h"
#include "shader.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include <QDebug>
//#include <QThread>
//#include <QOpenGLExtraFunctions>

//namespace  {

class Model {
public:
    /*  Model Data */
    QOpenGLFunctionsCore* m_fun;
    vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
//    std::string m_file;

    //    Model() {}

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    //    Model(string const& path, bool gamma = false)
    Model(const string& path)
        //        : gammaCorrection(gamma),
//        : m_file(path)
    {

        //        initializeOpenGLFunctions();
        //    fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
        //        fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
        //        m_fun = fun;
//        if (!fake) {
            m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
            //    qDebug() << QThread::currentThreadId() << "[MODEL]" << this << "[CONTEXT]" << fun;

            loadModel(g_resourcesPath + path);
            std::cout << "[MODEL] load : " << path << std::endl;
//        }
    }

//    bool operator==(const Model& model)
//    {
//        return m_file == model.m_file;
//    }

    // draws the model, and thus all its meshes
    void Draw(const Shader& shader)
    {
        //        qDebug() << "[MODEL]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();
        //        fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
        //        qDebug() << "[CONTEXT] model draw : " << fun;

        //        qDebug() << "nb mesh = " << meshes.size();

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

private:
//    static Assimp::Importer m_importer;
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path)
    {

        //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << m_fun;
        //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();
        // read file via ASSIMP
        Assimp::Importer m_importer;
//        qDebug() << "[MODEL] m_importer : " << &m_importer;
        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_FlipWindingOrder);
//        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded);
        qDebug() << "[MODEL]" << path.c_str() << "aiScene : " << scene << "importer" << &m_importer << "numMeshes" << scene->mNumMeshes;
        //        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << m_importer.GetErrorString() << endl;
            return;
        }
        // retrieve the directory path of the filepath
        directory = path.substr(0, path.find_last_of('/'));

        //        std::cout << "scene:";
        //        std::cout << ", numLights: " << scene->mNumLights;
        //        std::cout << ", numMeshes: " << scene->mNumMeshes;
        //        std::cout << ", numCameras: " << scene->mNumCameras;
        //        std::cout << ", numTextures: " << scene->mNumTextures;
        //        std::cout << ", numMaterials: " << scene->mNumMaterials;
        //        std::cout << ", numAnimations: " << scene->mNumAnimations << std::endl;

        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene, 0);
    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene, int depth)
    {
        //        for (int i = 0; i < depth; ++i) {
        //            std::cout << "\t";
        //        }
        //        std::cout << "node: " << node->mName.C_Str();
        //        std::cout << ", numMeshes: " << node->mNumMeshes;
        //        std::cout << ", numChildren: " << node->mNumChildren << std::endl;

        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            // the node object only contains indices to index the actual objects in the scene.
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene, depth + 1));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene, depth + 1);
        }
    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene, int depth)
    {
        //        for (int i = 0; i < depth; ++i) {
        //            std::cout << "\t";
        //        }
        //        std::cout << "mesh: " << mesh->mName.C_Str();
        //        std::cout << ", numBones: " << mesh->mNumBones;
        //        std::cout << ", numFaces: " << mesh->mNumFaces;
        //        std::cout << ", numVertices: " << mesh->mNumVertices;
        //        std::cout << ", numAnimMeshes: " << mesh->mNumAnimMeshes;
        //        std::cout << ", numUVComponents: ";
        //        for (int i = 0; i < 8; ++i) {
        //            std::cout << mesh->mNumUVComponents[i] << " ";
        //        }
        //        std::cout << ", hasPositions: " << mesh->HasPositions();
        //        std::cout << ", hasNormals: " << mesh->HasNormals();
        //        std::cout << ", hasVertexColors: " << mesh->HasVertexColors(0);
        //        std::cout << ", hasTextureCoords: " << mesh->HasTextureCoords(0);
        //        //        std::cout << ", hasTangentAndBitangenst: " << mesh->HasTangentsAndBitangents();
        //        std::cout << std::endl;

        // data to fill
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (!mesh->HasNormals()) {
                vector = glm::vec3(0.0);
            } else {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
            }
            vertex.Normal = vector;
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            } else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            if (mesh->HasTangentsAndBitangents()) {
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, textures);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++) {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip) { // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }

    //    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false)
    unsigned int TextureFromFile(const char* path, const string& directory)
    {
        string filename = string(path);
        filename = directory + '/' + filename;
        //        QOpenGLFunctionsCore* fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
        //        qDebug() << "model.h : " << fun;
        //        QOpenGLFunctions * fun = QOpenGLContext::currentContext()->functions();

        unsigned int textureID;
        m_fun->glGenTextures(1, &textureID);

        int width, height, nrComponents;
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
};

//    Assimp::Importer Model::m_importer;
//}

#endif
