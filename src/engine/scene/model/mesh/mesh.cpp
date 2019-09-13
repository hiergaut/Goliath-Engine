#include "mesh.h"

#include <assimp/Assimp.h>
#include <gui/editor/timeline/FormTimeline.h>

Mesh::Mesh(const aiMesh* ai_mesh, Materials* materials, Textures* textures)
    : m_materials(materials)
    , m_textures(textures)
    , m_name(ai_mesh->mName.C_Str())
{
    const uint numVertices = ai_mesh->mNumVertices;
    //    m_box = new BoundingBox;

    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    m_box = new BoundingBox;

    m_bones.reserve(100);
    //        fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun =
    //        initializeOpenGLFunctions();
    //    m_numAnimMesh = ai_mesh->mNumAnimMeshes;
    Q_ASSERT(ai_mesh->mNumAnimMeshes == 0);

    //        std::cout << std::endl;
    //    Mesh mesh(ai_mesh->mName.C_Str());
    m_numFaces = ai_mesh->mNumFaces;
    m_iMaterial = ai_mesh->mMaterialIndex;

    // -------------------------------- INDICES
    m_indices.clear();
    m_triangles.clear();
    m_triangles.resize(numVertices);
    for (uint i = 0; i < ai_mesh->mNumFaces; ++i) {
        aiFace* ai_face = &ai_mesh->mFaces[i];
        //        Face face;
        //        Q_ASSERT(ai_face->mNumIndices == 3);
        //        mesh.m_lenFaces.push_back(ai_face->mNumIndices);

        for (uint j = 0; j < ai_face->mNumIndices; ++j) {
            uint indice = ai_face->mIndices[j];
            //            face.m_indices.push_back(indice);
            //            m_indices.push_back(indice);
            m_indices.emplace_back(indice);

            m_triangles[indice].insert(i);
        }
        //        mesh.m_faces.push_back(face);
    }
    Q_ASSERT(m_indices.size() == 3 * ai_mesh->mNumFaces);

    // -------------------------------- BONES
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
        m_bones.emplace_back(ai_bone, m_indices);

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

    // -------------------------------- VERTICES
    m_vertices.clear();
    for (uint i = 0; i < numVertices; ++i) {
        Vertex v;
        //        const aiVector3D* ai_vertex = &ai_mesh->mVertices[i];
        //        glm::vec3 vertex(ai_vertice->x, ai_vertice->y, ai_vertice->z);
        //        v.Position = glm::vec3(ai_vertex->x, ai_vertex->y, ai_vertex->z);
        v.Position = aiVec3ToGlm(ai_mesh->mVertices[i]);
        if (ai_mesh->HasNormals()) {
            v.Normal = aiVec3ToGlm(ai_mesh->mNormals[i]);
        }
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
    //    m_box = new BoundingBox;
    //    initBonesBoundingBox();
}

Mesh::Mesh(std::ifstream& file, Materials* materials, Textures* textures)
    : m_materials(materials)
    , m_textures(textures)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    m_box = new BoundingBox;
    //    m_box = new BoundingBox;
    m_bones.reserve(100);

    uint size;
    //    std::cout << "m_bones" << std::endl;

    //    std::cout << "m_transform" << std::endl;
    Session::load(m_transform, file);
    //    std::cout << "m_iMaterial" << std::endl;
    Session::load(m_iMaterial, file);
    //    std::cout << "m_name" << std::endl;
    Session::load(m_name, file);

    //    std::cout << "m_vertices" << std::endl;
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_vertices.emplace_back(file);
    }

    //    std::cout << "m_bonesData" << std::endl;
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_bonesData.emplace_back(file);
    }

    //    std::cout << "m_sumBoneWeights" << std::endl;
    Session::load(m_sumBoneWeights, file);
    //    std::cout << "m_numFaces" << std::endl;
    Session::load(m_numFaces, file);

    //    std::cout << "m_indices" << std::endl;
    Session::load(m_indices, file);
    m_triangles.clear();
    m_triangles.resize(m_vertices.size());
    for (uint i = 0; i < m_indices.size() / 3; ++i) {
        //        aiFace* ai_face = &ai_mesh->mFaces[i];
        //        Face face;
        //        Q_ASSERT(ai_face->mNumIndices == 3);
        //        mesh.m_lenFaces.push_back(ai_face->mNumIndices);
        uint i3 = i * 3;

        for (uint j = 0; j < 3; ++j) {
            uint indice = m_indices[i3 + j];
            //            face.m_indices.push_back(indice);
            //            m_indices.push_back(indice);
            //            m_indices.emplace_back(indice);

            m_triangles[indice].insert(i);
        }
        //        mesh.m_faces.push_back(face);
    }
    //    Q_ASSERT(m_indices.size() == 3 * ai_mesh->mNumFaces);
    //    Session::load(m_bbo)
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_bones.emplace_back(file, m_indices);
    }

    setupMesh();
    //    std::cout << "\033[32m";
    //    std::cout << "[MESH] " << m_name << " created " << this << std::endl;
    //    std::cout << "\033[0m";
    //    m_box = new BoundingBox;
    //    initBonesBoundingBox();
}

//Mesh::Mesh(const Mesh &mesh)
//    : m_materials(mesh.m_materials)
//    , m_textures(mesh.m_textures)
//{
//    std::cout << "\033[31m";
//    std::cout << "[MESH] '" << m_name << "' copy constructor " << this << std::endl;
//    std::cout << "\033[0m";

//}

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
    std::cout << "\033[35m";
    std::cout << "[MESH] '" << m_name << "' deleted " << this << std::endl;
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

    const Material& material = (*m_materials)[m_iMaterial];
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
    // draw mesh
    m_fun->glBindVertexArray(m_vao);

    //    glPointSize(5.0f);
    m_fun->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    m_fun->glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    m_fun->glActiveTexture(GL_TEXTURE0);
}

void Mesh::draw(const Shader& shader, bool dotCloud) const
{
//    qDebug() << "context " << m_fun;
    //    Q_ASSERT(m_box != nullptr);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    shader.setMat4("model", m_transform);
    //    shader.setMat4("model", glm::mat4(1));

    if (shader.m_shade == Shader::Type::LOOK_DEV || shader.m_shade == Shader::Type::RENDERED) {
        const Material& material = (*m_materials)[m_iMaterial];
        //        const Material& material = mesh.m_material;
        //        const Material& material = mesh.m_material;

        //    for (uint diffuse : material.m_diffuseMaps) {
        //    for (uint i = 0; i < material.m_diffuseMaps.size();++i) {
        //        for (uint i =0; i <material.m_iTextures->size(); ++i) {
        //                const Texture& texture = m_textures[material.m_iTextures[i]];

        //        }
        bool hasTexture = false;
        uint cpt = 0;
        for (uint i = 0; i < Texture::size; ++i) {
            for (uint j = 0; j < material.m_iTextures[i].size(); ++j) {
                hasTexture = true;
                const Texture& texture = (*m_textures)[material.m_iTextures[i][j]];

                m_fun->glActiveTexture(GL_TEXTURE0 + cpt);
                std::string number = std::to_string(j);
                std::string name = std::string(texture);
                m_fun->glUniform1i(m_fun->glGetUniformLocation(shader.ID, (name + number).c_str()), cpt);
                m_fun->glBindTexture(GL_TEXTURE_2D, texture.m_id);

                ++cpt;
                //            }
            }
        }

        shader.setBool("hasTexture", hasTexture);
        if (!hasTexture) {
            shader.setVec3("material.ambient", material.m_colors[Color::AMBIENT]);
        }
        //        shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
        //            shader.setVec3("material.diffuse", 0.3f, 0.3f, 0.3f);
        //        shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);

        shader.setVec3("material.specular", material.m_colors[Color::SPECULAR]);
        //        shader.setVec3("material.specular", material.m_colors[Color::DIFFUSE]);
        shader.setFloat("material.shininess", material.m_shininess);
    }
    //    if (shade == MainWindow3dView::Shading::RENDERED) {

    //    }

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

    //    glPointSize(5.0f);
    if (dotCloud)
        m_fun->glDrawArrays(GL_POINTS, 0, m_vertices.size());
    //        m_fun->glDrawElements(GL_POINTS, m_vertices.size(), GL_UNSIGNED_INT, 0);

    else
        m_fun->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    m_fun->glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    m_fun->glActiveTexture(GL_TEXTURE0);
}

void Mesh::drawBoundingBox(const Shader& shader) const
{
    //    shader.use();
    //    BoundingBox box;

    for (uint i = 0; i < m_bones.size(); ++i) {
        //    for (const Bone & bone : m_bones) {
        const Bone& bone = m_bones[i];

        uint id = i;
        float r, g, b;
        r = (id % 3) / 2.0f;
        id /= 3;
        g = (id % 3) / 2.0f;
        id /= 3;
        b = (id % 3) / 2.0f;

        shader.setVec4("color", glm::vec4(r, g, b, 1.0f));

        bone.m_box.draw(shader);
        //        box << bone.m_box;
        //        m_box.draw(modelMatrix, shader);
    }

    //    box.draw(modelMatrix, shader);
}

void Mesh::save(std::ofstream& file) const
{
    uint size;

    //    std::cout << "m_bones" << std::endl;

    //    std::cout << "m_transform" << std::endl;
    Session::save(m_transform, file);
    //    std::cout << "m_iMaterial" << std::endl;
    Session::save(m_iMaterial, file);
    //    std::cout << "m_name" << std::endl;
    Session::save(m_name, file);

    //    std::cout << "m_vertices" << std::endl;
    size = m_vertices.size();
    Session::save(size, file);
    for (uint i = 0; i < size; ++i) {
        //        m_vertices.emplace_back(file);
        m_vertices[i].save(file);
    }

    //    std::cout << "m_bonesData" << std::endl;
    size = m_bonesData.size();
    Session::save(size, file);
    for (uint i = 0; i < size; ++i) {
        //        m_bonesData.emplace_back(file);
        m_bonesData[i].save(file);
    }

    //    std::cout << "m_sumBoneWeights" << std::endl;
    Session::save(m_sumBoneWeights, file);
    //    std::cout << "m_numFaces" << std::endl;
    Session::save(m_numFaces, file);

    //    std::cout << "m_indices" << std::endl;
    Session::save(m_indices, file);
    //    Session::load(m_bbo)
    size = m_bones.size();
    Session::save(size, file);
    for (uint i = 0; i < size; ++i) {
        //        m_bones.emplace_back(file);
        m_bones[i].save(file);
    }
}

//void Mesh::initBonesBoundingBox() const
//{
//    //    m_box.clear();
//    //    for (const Vertex & vertex : m_vertices) {
//    //        m_box << vertex.Position;
//    //    }
//    for (const Bone& bone : m_bones) {
//        bone.m_box.clear();

//        for (auto& pair : bone.m_weights) {
//            uint indice = pair.first;
////            glm::vec3 pos = m_vertices[indice].Position;
////            bone.m_box << pos;
//            uint first = indice - indice % 3;

//            for (uint i = 0; i < 3; ++i) {
//                glm::vec3 pos = bone.m_transform * glm::vec4(m_vertices[first + i].Position, 0.0);

//                bone.m_box << pos;
//            }
//        }
//    }
//}

void Mesh::updateBoundingBox(const glm::mat4& modelTransform) const
{
    //    m_box.m_cube.setupGL();
    m_box.clear();
    //    m_box = std::move(BoundingBox());
    if (m_bones.size() == 0) {
        for (const Vertex& vertex : m_vertices) {
            const glm::vec3& pos = modelTransform * m_transform * glm::vec4(vertex.Position, 1.0);

            m_box << pos;
        }

    } else {
        for (const Bone& bone : m_bones) {
            bone.m_box.clear();

            // question : doublon indice ?
            for (auto& pair : bone.m_weights) {
                //                            glm::vec3 pos = bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(m_vertices[pair.first].Position, 1.0);
                //                            bone.m_box << pos;
                //                            continue;

                uint indice = pair.first;
                uint first = indice - indice % 3;

                for (uint i = 0; i < 3; ++i) {
                    glm::vec3 pos = modelTransform * bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(m_vertices[first + i].Position, 1.0);
                    //                glm::vec3 pos = m_vertices[first + i].Position;

                    bone.m_box << pos;
                    //                m_box << pos;
                }
            }
            m_box << bone.m_box;
        }
    }

    //    m_box.clear();
    //    for (const Bone& bone : m_bones) {
    //        if (FormTimeline::animation() == nullptr) {
    //            m_box << bone.m_box;
    //        } else {
    //            m_box << bone.m_box * bone.m_transform;
    //            //            m_box << bone.m_transform * bone.m_box;
    //        }
    //        //        m_box << bone.min();
    //        //        m_box << bone.max();
    //    }
}
