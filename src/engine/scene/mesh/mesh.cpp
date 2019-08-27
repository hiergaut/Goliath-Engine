#include "mesh.h"

#include <assimp/Assimp.h>
#include <gui/editor/timeline/FormTimeline.h>

Mesh::Mesh(const aiMesh* ai_mesh, const Materials& materials, const Textures& textures)
    : m_name(ai_mesh->mName.C_Str())
    , m_materials(materials)
    , m_textures(textures)
{
    const uint numVertices = ai_mesh->mNumVertices;

    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    m_bones.reserve(50);
    //        fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun =
    //        initializeOpenGLFunctions();
    //    m_numAnimMesh = ai_mesh->mNumAnimMeshes;
    Q_ASSERT(ai_mesh->mNumAnimMeshes == 0);

    //    m_bonesData.resize(numVertices);
    VertexBoneData vBone;
    m_bonesData = std::vector<VertexBoneData>(numVertices, vBone);

    //    int cpt[ai_mesh->mNumVertices] = {0};
    std::vector<uint> cpts(numVertices, 0);

    m_sumBoneWeights = 0;
    for (uint i = 0; i < ai_mesh->mNumBones; ++i) {
        const aiBone* ai_bone = ai_mesh->mBones[i];
        m_sumBoneWeights += ai_bone->mNumWeights;
        //        m_bones.push_back(Bone(ai_bone));
        m_bones.emplace_back(ai_bone);

        for (uint j = 0; j < ai_bone->mNumWeights; ++j) {
            const aiVertexWeight& ai_vertexWeight = ai_bone->mWeights[j];

            const uint vid = ai_vertexWeight.mVertexId;
            uint& cpt = cpts[vid];

            m_bonesData[vid].IDs[cpt] = i;
            m_bonesData[vid].Weights[cpt] = ai_vertexWeight.mWeight;
            ++cpt;
        }
    }
    Q_ASSERT(ai_mesh->mNumBones < 100);

    //        std::cout << std::endl;
    //    Mesh mesh(ai_mesh->mName.C_Str());
    m_numFaces = ai_mesh->mNumFaces;
    m_iMaterial = ai_mesh->mMaterialIndex;

    m_indices.clear();
    for (int i = 0; i < ai_mesh->mNumFaces; ++i) {
        aiFace* ai_face = &ai_mesh->mFaces[i];
        //        Face face;
        //        Q_ASSERT(ai_face->mNumIndices == 3);
        //        mesh.m_lenFaces.push_back(ai_face->mNumIndices);

        for (int j = 0; j < ai_face->mNumIndices; ++j) {
            uint indice = ai_face->mIndices[j];
            //            face.m_indices.push_back(indice);
            //            m_indices.push_back(indice);
            m_indices.emplace_back(indice);
        }
        //        mesh.m_faces.push_back(face);
    }
    Q_ASSERT(m_indices.size() == 3 * ai_mesh->mNumFaces);

    m_vertices.clear();
    for (uint i = 0; i < numVertices; ++i) {
        Vertex v;
        //        const aiVector3D* ai_vertex = &ai_mesh->mVertices[i];
        //        glm::vec3 vertex(ai_vertice->x, ai_vertice->y, ai_vertice->z);
        //        v.Position = glm::vec3(ai_vertex->x, ai_vertex->y, ai_vertex->z);
        v.Position = aiVec3ToGlm(ai_mesh->mVertices[i]);
        v.Normal = aiVec3ToGlm(ai_mesh->mNormals[i]);
        //        v.TexCoords = aiVec2ToGlm(ai_mesh->mTextureCoords[i]);

        if (ai_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = ai_mesh->mTextureCoords[0][i].x;
            vec.y = ai_mesh->mTextureCoords[0][i].y;
            v.TexCoords = vec;

        } else {
            v.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        //        m_vertices.push_back(std::move(v));
        m_vertices.emplace_back(v);
    }
    Q_ASSERT(m_vertices.size() == numVertices);

    m_transform = glm::mat4(1.0f);

    setupMesh();
    //    return std::move(mesh);
    //    std::cout << "\033[32m";
    //    std::cout << "[MESH] " << m_name << " created " << this << std::endl;
    //    std::cout << "\033[0m";
}

Mesh::Mesh(std::ifstream &file, const Materials &materials, const Textures &textures)
    : m_materials(materials)
    , m_textures(textures)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    m_bones.reserve(50);

    uint size;
    Session::load(size, file);
    for (uint i =0; i <size; ++i) {
        m_bones.emplace_back(file);
    }

    Session::load(m_transform, file);
    Session::load(m_iMaterial, file);
    Session::load(m_name, file);

    Session::load(size, file);
    for (uint i =0; i <size; ++i) {
        m_vertices.emplace_back(file);
    }

    Session::load(size, file);
    for (uint i =0; i <size; ++i) {
        m_bonesData.emplace_back(file);
    }

    Session::load(m_sumBoneWeights, file);
    Session::load(m_numFaces, file);

    Session::load(m_indices, file);
//    Session::load(m_bbo)

    setupMesh();
}

//Mesh::Mesh(Mesh &&mesh) noexcept
//{
//    m_fun = mesh.m_fun;
//    m_name = mesh.m_name;
//    m_indices = std::move(mesh.m_indices);
//    m_vertices = std::move(mesh.m_vertices);
//    m_iMaterial = mesh.m_iMaterial;
//    VAO = mesh.VAO;
//    VBO = mesh.VBO;
//    EBO = mesh.EBO;

//}

Mesh::~Mesh()
{
    //    qDebug() << "[Model] destruct " << this;
    std::cout << "\033[31m";
    std::cout << "[MESH] " << m_name << " deleted " << this << std::endl;
    std::cout << "\033[0m";

    //    delete m_rootNode;

    //    if (m_rootNode != nullptr)
}

void Mesh::buildItemModel(QStandardItem* parent) const
{

    //    QStandardItem * item = new QStandardItem(mesh->m_name.c_str());
    QStandardItem* item = new QStandardItem(QIcon(":/icons/mesh.png"), QString(m_name.c_str()) + "  f:" + QString::number(m_numFaces) + "  v:" + QString::number(m_vertices.size()));
    parent->appendRow(item);

    //    QStandardItem * item2 = new QStandardItem("num anim mesh " + QString::number(mesh.m_numAnimMesh));
    //    item->appendRow(item2);

    const Material& material = m_materials[m_iMaterial];
    //    modelRecurseMaterial(material, item);
    //    QStandardItem* item2 = new QStandardItem(material.m_name.c_str());
    //    QStandardItem * item2 = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());
    //    item->appendRow(item2);
    material.buildItemModel(item);

    //        QStandardItem * item2 = new QStandardItem(QIcon)
    QStandardItem* item3 = new QStandardItem(QIcon(":/icons/vertexGroups.png"), "Vertex Groups  bones:" + QString::number(m_bones.size()) + "  sumBoneWeights:" + QString::number(m_sumBoneWeights));
    item->appendRow(item3);
    //    for (const Bone& bone : m_bones) {
    //        bone.buildItemModel(item3);
    //    }
}

/*  Functions    */
// initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        QOpenGLFunctions * fun = QOpenGLContext::currentContext()->functions();
    //        QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();

    // create buffers/arrays
    m_fun->glGenVertexArrays(1, &m_vao);
    m_fun->glGenBuffers(1, &VBO);
    m_fun->glGenBuffers(1, &EBO);
    m_fun->glGenBuffers(1, &m_bbo);

    m_fun->glBindVertexArray(m_vao);
    // load data into vertex buffers
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //    std::vector<uint> indices;
    //    for (int i =0; i <m_faces.size(); ++i) {
    //        const Face & face = m_faces[i];
    //        indices.insert(indices.end(), face.m_indices.begin(), face.m_indices.end());
    //    }

    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_faces[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    m_fun->glEnableVertexAttribArray(1);
    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    m_fun->glEnableVertexAttribArray(2);
    m_fun->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    //    m_fun->glEnableVertexAttribArray(3);
    //    m_fun->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    //    // vertex bitangent
    //    m_fun->glEnableVertexAttribArray(4);
    //    m_fun->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_bbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_bonesData.size() * sizeof(VertexBoneData), &m_bonesData[0], GL_STATIC_DRAW);

    m_fun->glEnableVertexAttribArray(3);
    m_fun->glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);

    m_fun->glEnableVertexAttribArray(4);
    m_fun->glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void*)16);

    m_fun->glBindVertexArray(0);
}

void Mesh::draw(const Shader& shader) const
{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    shader.setMat4("model", m_transform);
    //    shader.setMat4("model", glm::mat4(1));

    const Material& material = m_materials[m_iMaterial];
    //        const Material& material = mesh.m_material;
    //        const Material& material = mesh.m_material;

    //    for (uint diffuse : material.m_diffuseMaps) {
    //    for (uint i = 0; i < material.m_diffuseMaps.size();++i) {
    //        for (uint i =0; i <material.m_iTextures->size(); ++i) {
    //                const Texture& texture = m_textures[material.m_iTextures[i]];

    //        }
    uint cpt = 0;
    for (uint i = 0; i < Texture::size; ++i) {
        for (uint j = 0; j < material.m_iTextures[i].size(); ++j) {
            const Texture& texture = m_textures[material.m_iTextures[i][j]];

            m_fun->glActiveTexture(GL_TEXTURE0 + cpt);
            std::string number = std::to_string(j);
            std::string name = std::string(texture);
            m_fun->glUniform1i(m_fun->glGetUniformLocation(shader.ID, (name + number).c_str()), cpt);
            m_fun->glBindTexture(GL_TEXTURE_2D, texture.m_id);

            ++cpt;
            //            }
        }
    }

    if (FormTimeline::animation() != nullptr) {
        if (m_bones.size() > 0) {
            for (uint i = 0; i < m_bones.size(); ++i) {
                const Bone& bone = m_bones[i];

                shader.setMat4("gBones[" + std::to_string(i) + "]", bone.m_transform);
                //        shader.setMat4("gBones[" + std::to_string(i) +"]", bone.m_transform * bone.m_offsetMatrix);
            }
            shader.setBool("isSkeleton", true);
        } else {
            shader.setBool("isSkeleton", false);
        }
    } else {
        shader.setBool("isSkeleton", false);
    }
    //    // draw mesh
    //    m_fun->glBindVertexArray(m_vao);
    //    m_fun->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    //    m_fun->glBindVertexArray(0);

    //    shader.setBool("isSkeleton", true);
    // draw mesh
    m_fun->glBindVertexArray(m_vao);
    m_fun->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    m_fun->glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    m_fun->glActiveTexture(GL_TEXTURE0);
}

void Mesh::save(std::ofstream &file) const
{

}
