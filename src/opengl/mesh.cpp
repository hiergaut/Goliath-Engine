#include "mesh.h"

Mesh::Mesh(std::string name)
    : m_name(name)
{
    //        fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun =
    //        initializeOpenGLFunctions();

    //        this->vertices = vertices;
    //        this->indices = indices;
    //        this->textures = textures;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    //        setupMesh();
}

//Mesh::operator QString() const
//{
//    //        std::string str = "fuck";
//    //        std::ostream str;
//    //        str += "nb vertices : " + vertices.size();
//    //        str += ", nb indices : " + indices.size();
//    //        str += ", nb textures : " + textures.size();
//    //        return QString("vertices:" + QString::number(vertices.size()) + ", indices:" + QString::number(indices.size()) + ", textures:" + QString::number(textures.size()));
//    return QString(QString::number(vertices.size()) + "  " + QString::number(indices.size()) + "  " + QString::number(textures.size()));
//    //        return str.c_str();
//}

// render the mesh
void Mesh::Draw(const Shader& shader)
{
//            QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        qDebug() << "mesh.h : " << fun;

    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->extraFunctions<QOpenGLFunctionsCore>();
    //        fun = QOpenGLContext::currentContext()->extraFunctions();
    //        QOpenGLFunctions * fun = QOpenGLContext::currentContext()->functions();
    //        QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();
    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext();
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        m_fun->glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        m_fun->glUniform1i(m_fun->glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        m_fun->glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    m_fun->glBindVertexArray(VAO);
    m_fun->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    m_fun->glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    m_fun->glActiveTexture(GL_TEXTURE0);
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
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
//    m_fun->glEnableVertexAttribArray(1);
//    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//    // vertex texture coords
//    m_fun->glEnableVertexAttribArray(2);
//    m_fun->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//    // vertex tangent
//    m_fun->glEnableVertexAttribArray(3);
//    m_fun->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
//    // vertex bitangent
//    m_fun->glEnableVertexAttribArray(4);
//    m_fun->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    m_fun->glBindVertexArray(0);
}
