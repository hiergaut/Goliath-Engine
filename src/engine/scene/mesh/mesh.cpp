#include "mesh.h"

#include <assimp/Assimp.h>

Mesh::Mesh(const aiMesh * ai_mesh)
    : m_name(ai_mesh->mName.C_Str())
{
    //        fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun =
    //        initializeOpenGLFunctions();

//    for (uint i =0; i <ai_mesh->mNumBones; ++i) {
//        const aiBone * ai_bone = ai_mesh->mBones[i];
//        m_bones.push_back(Bone(ai_bone));
//    }

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
    for (uint i = 0; i < ai_mesh->mNumVertices; ++i) {
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
    Q_ASSERT(m_vertices.size() == ai_mesh->mNumVertices);

    setupMesh();
//    return std::move(mesh);
//    std::cout << "\033[32m";
//    std::cout << "[MESH] " << m_name << " created " << this << std::endl;
//    std::cout << "\033[0m";
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


/*  Functions    */
// initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        QOpenGLFunctions * fun = QOpenGLContext::currentContext()->functions();
    //        QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();

    // create buffers/arrays
    m_fun->glGenVertexArrays(1, &VAO);
    m_fun->glGenBuffers(1, &VBO);
    m_fun->glGenBuffers(1, &EBO);

    m_fun->glBindVertexArray(VAO);
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

    m_fun->glBindVertexArray(0);
}
