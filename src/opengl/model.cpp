#include "model.h"
#include <QFileInfo>

QImage loadTga(const char* filePath, bool &success)
{
    QImage img;
    if (!img.load(filePath))
    {

        // open the file
        std::fstream fsPicture(filePath, std::ios::in | std::ios::binary);

        if (!fsPicture.is_open())
        {
            img = QImage(1, 1, QImage::Format_RGB32);
            img.fill(Qt::red);
            success = false;
            return img;
        }

        // some variables
        std::vector<std::uint8_t>* vui8Pixels;
        std::uint32_t ui32BpP;
        std::uint32_t ui32Width;
        std::uint32_t ui32Height;

        // read in the header
        std::uint8_t ui8x18Header[19] = { 0 };
        fsPicture.read(reinterpret_cast<char*>(&ui8x18Header), sizeof(ui8x18Header) - 1);

        //get variables
        vui8Pixels = new std::vector<std::uint8_t>;
        bool bCompressed;
        std::uint32_t ui32IDLength;
        std::uint32_t ui32PicType;
        std::uint32_t ui32PaletteLength;
        std::uint32_t ui32Size;

        // extract all information from header
        ui32IDLength = ui8x18Header[0];
        ui32PicType = ui8x18Header[2];
        ui32PaletteLength = ui8x18Header[6] * 0x100 + ui8x18Header[5];
        ui32Width = ui8x18Header[13] * 0x100 + ui8x18Header[12];
        ui32Height = ui8x18Header[15] * 0x100 + ui8x18Header[14];
        ui32BpP = ui8x18Header[16];

        // calculate some more information
        ui32Size = ui32Width * ui32Height * ui32BpP / 8;
        bCompressed = ui32PicType == 9 || ui32PicType == 10;
        vui8Pixels->resize(ui32Size);

        // jump to the data block
        fsPicture.seekg(ui32IDLength + ui32PaletteLength, std::ios_base::cur);

        if (ui32PicType == 2 && (ui32BpP == 24 || ui32BpP == 32))
        {
            fsPicture.read(reinterpret_cast<char*>(vui8Pixels->data()), ui32Size);
        }
        // else if compressed 24 or 32 bit
        else if (ui32PicType == 10 && (ui32BpP == 24 || ui32BpP == 32))	// compressed
        {
            std::uint8_t tempChunkHeader;
            std::uint8_t tempData[5];
            unsigned int tempByteIndex = 0;

            do {
                fsPicture.read(reinterpret_cast<char*>(&tempChunkHeader), sizeof(tempChunkHeader));

                if (tempChunkHeader >> 7)	// repeat count
                {
                    // just use the first 7 bits
                    tempChunkHeader = (uint8_t(tempChunkHeader << 1) >> 1);

                    fsPicture.read(reinterpret_cast<char*>(&tempData), ui32BpP / 8);

                    for (int i = 0; i <= tempChunkHeader; i++)
                    {
                        vui8Pixels->at(tempByteIndex++) = tempData[0];
                        vui8Pixels->at(tempByteIndex++) = tempData[1];
                        vui8Pixels->at(tempByteIndex++) = tempData[2];
                        if (ui32BpP == 32) vui8Pixels->at(tempByteIndex++) = tempData[3];
                    }
                }
                else						// data count
                {
                    // just use the first 7 bits
                    tempChunkHeader = (uint8_t(tempChunkHeader << 1) >> 1);

                    for (int i = 0; i <= tempChunkHeader; i++)
                    {
                        fsPicture.read(reinterpret_cast<char*>(&tempData), ui32BpP / 8);

                        vui8Pixels->at(tempByteIndex++) = tempData[0];
                        vui8Pixels->at(tempByteIndex++) = tempData[1];
                        vui8Pixels->at(tempByteIndex++) = tempData[2];
                        if (ui32BpP == 32) vui8Pixels->at(tempByteIndex++) = tempData[3];
                    }
                }
            } while (tempByteIndex < ui32Size);
        }
        // not useable format
        else
        {
            fsPicture.close();
            img = QImage(1, 1, QImage::Format_RGB32);
            img.fill(Qt::red);
            success = false;
            return img;
        }

        fsPicture.close();

        img = QImage(ui32Width, ui32Height, QImage::Format_RGB888);

        int pixelSize = ui32BpP == 32 ? 4 : 3;
        //TODO: write direct into img
        for (unsigned int x = 0; x < ui32Width; x++)
        {
            for (unsigned int y = 0; y < ui32Height; y++)
            {
                int valr = vui8Pixels->at(y * ui32Width * pixelSize + x * pixelSize + 2);
                int valg = vui8Pixels->at(y * ui32Width * pixelSize + x * pixelSize + 1);
                int valb = vui8Pixels->at(y * ui32Width * pixelSize + x * pixelSize);

                QColor value(valr, valg, valb);
                img.setPixelColor(x, y, value);
            }
        }

        img = img.mirrored();

    }
    success = true;
    return img;
}

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from)
{
    glm::mat4 to;
    //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to[0][0] = from.a1;
    to[1][0] = from.a2;
    to[2][0] = from.a3;
    to[3][0] = from.a4;
    to[0][1] = from.b1;
    to[1][1] = from.b2;
    to[2][1] = from.b3;
    to[3][1] = from.b4;
    to[0][2] = from.c1;
    to[1][2] = from.c2;
    to[2][2] = from.c3;
    to[3][2] = from.c4;
    to[0][3] = from.d1;
    to[1][3] = from.d2;
    to[2][3] = from.d3;
    to[3][3] = from.d4;
    return to;
}

glm::vec3 aiVec3ToGlm(const aiVector3D& from)
{
    return glm::vec3(from.x, from.y, from.z);
}

glm::vec3 aiColor3ToGlm(const aiColor3D& from) {
    return glm::vec3(from.r, from.g, from.b);
}

glm::vec2 aiVec2ToGlm(const aiVector2D& from)
{
    return glm::vec2(from.x, from.y);
}

Model::Model(const std::string& path)
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

    assimpLoadModel(g_resourcesPath + path);
    std::cout << "[MODEL] load : " << path << std::endl;
    //        }
}

//    bool operator==(const Model& model)
//    {
//        return m_file == model.m_file;
//    }

// draws the model, and thus all its meshes
void Model::Draw(const Shader& shader)
{
    //        qDebug() << "[MODEL]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();
    //        fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        qDebug() << "[CONTEXT] model draw : " << fun;

    //        qDebug() << "nb mesh = " << meshes.size();

    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        //        m_meshes[i].Draw(shader, this);

        const Mesh& mesh = m_meshes[i];

        const Material& material = m_materials[mesh.m_material];
        uint cpt = 0;
        //    for (uint diffuse : material.m_diffuseMaps) {
        //    for (uint i = 0; i < material.m_diffuseMaps.size();++i) {
        for (uint i = 0; i < Texture::e_type::size; ++i) {
            for (uint j = 0; j < material.m_textures[i].size(); ++j) {
                const Texture& texture = m_textures[material.m_textures[i][j]];

                m_fun->glActiveTexture(GL_TEXTURE0 + cpt);
                std::string number = std::to_string(j);
                std::string name = std::string(texture);
                m_fun->glUniform1i(m_fun->glGetUniformLocation(shader.ID, (name + number).c_str()), cpt);
                m_fun->glBindTexture(GL_TEXTURE_2D, texture.id);

                ++cpt;
            }
        }

        shader.setVec3("material.ambient", material.m_colorAmbient);
//        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;
        shader.setVec3("material.diffuse", material.m_colorDiffuse);
        shader.setVec3("material.specular", material.m_colorSpecular);
        shader.setFloat("material.shininess", material.m_shininess);

//        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;

//        shader.setVec3()
        //    for (uint i =0; i <m_material)

        // draw mesh
        m_fun->glBindVertexArray(mesh.VAO);
        m_fun->glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
        m_fun->glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        m_fun->glActiveTexture(GL_TEXTURE0);
    }
}

void Model::modelBuild(QStandardItem* parent) const
{
    //    Q_ASSERT(scene != nullptr);
    //            std::cout << std::flush;

    //    for (int i =0; i <m_materials.size(); ++i) {
    //    const Material& material = m_materials[i];
    //    QStandardItem* item = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());
    //    parent->appendRow(item);
    //    }

    modelRecurseNode(m_rootNode, parent);

    //    QStandardItem* item2 = new QStandardItem("fuck");
    //    parent->appendColumn({item2});
}

void Model::modelRecurseNode(const Node* node, QStandardItem* parent) const
{
    //    Q_ASSERT(scene != nullptr);

    //    qDebug() << "node : '" << node->m_name.c_str() << "'";
    QStandardItem* item = new QStandardItem(QIcon(":/icons/node.png"), node->m_name.c_str());
    parent->appendRow(item);

    //    QStandardItem* item2 = new QStandardItem("fuck");
    //    parent->appendColumn({item2});

    //    const glm::mat4& m = node->m_transformation;
    //    modelMat4(node->m_transformation, item);

    for (int i = 0; i < node->m_numChildren; ++i) {
        modelRecurseNode(node->m_children[i], item);
    }

    for (int i = 0; i < node->m_numMeshes; ++i) {
        //        QStandardItem * item2 = new QStandardItem("mesh:" + QString::number(node->m_meshes[i]) + ", " + m_meshes[node->m_meshes[i]]);
        //        QStandardItem * item2 = new QStandardItem(QString::number(node->m_meshes[i]) + "  " + m_meshes[node->m_meshes[i]]);

        modelRecurseMesh(&m_meshes[node->m_meshes[i]], item);
        //        QStandardItem * item2 = new QStandardItem("mesh : " + QString::number(node->m_meshes[i]));
        //        item->appendRow(item2);
    }

    //    parent->appendRow(new QStandardItem(str));
}

void Model::modelRecurseMesh(const Mesh* mesh, QStandardItem* parent) const
{
    //    QStandardItem * item = new QStandardItem(mesh->m_name.c_str());
    QStandardItem* item = new QStandardItem(QIcon(":/icons/mesh.png"), QString(mesh->m_name.c_str()) + "  f:" + QString::number(mesh->m_numFaces) + "  v:" + QString::number(mesh->m_vertices.size()));
    parent->appendRow(item);

    const Material& material = m_materials[mesh->m_material];
    QStandardItem* item2 = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());

    for (int i = 0; i < Texture::e_type::size; ++i) {
        for (int j = 0; j < material.m_textures[i].size(); ++j) {
            const Texture& texture = m_textures[material.m_textures[i][j]];

            //            QString path = QString(texture.path.c_str());
//            QPixmap pixmap(texture.path.c_str());
//            bool success;
//            QImage image = loadTga(texture.path.c_str(), success);
//            Q_ASSERT(success);
////            Q_ASSERT(! image.isNull());
////            QPixmap pixmap(image);
//            QPixmap pixmap(QPixmap::fromImage(image));

            //            qDebug() << "path = " << path;
            QStandardItem* item3 = new QStandardItem(QIcon(texture.pixmap), QString(texture));
            item2->appendRow(item3);
        }
    }
    item->appendRow(item2);

    //    QStandardItem* item4 = new QStandardItem("vertices");
    //    //    int cpt =0;
    //    for (int i = 0; i < mesh->m_vertices.size(); ++i) {
    //        //            QStandardItem * item2 = new QStandardItem("face");
    //        const Vertex& v = mesh->m_vertices[i];
    //        QStandardItem* item5 = new QStandardItem(v);

    //        item4->appendRow(item5);
    //    }
    //    item->appendRow(item4);

    //            item->appendRow(item2);
    //            const Face* face = &mesh->m_faces[i];

    //            QStandardItem* item2 = new QStandardItem("face " + QString::number(i) + "  v:" + QString::number(face->m_indices.size()));

    //        for (int i = 0; i < face->m_indices.size(); ++i) {
    //            Vertice
    //            const Vertex* vertex = &mesh->m_vertices[face->m_indices[i]];

    //            modelVertex(vertex, item2);
    //            QStandardItem* item3 = new QStandardItem(QString::number(vertex->x) + " " + QString::number(vertex->y) + " " + QString::number(vertex->z));
    //            item2->appendRow(item3);

    //            item->appendRow(vertex);
    //        }

    //        item->appendRow(item2);

    //        modelRecurseFace(&mesh->m_faces[i], item);
}

//void Model::modelRecurseFace(const Face* face, QStandardItem* parent) const
//{
//    QStandardItem* item = new QStandardItem("face");

//    for (int i = 0; i < face->m_faces.size(); ++i) {
//        QStandardItem* vertex = new QStandardItem("vertex");
//        item->appendRow(vertex);
//    }

//    parent->appendRow(item);
//}

void Model::modelMat4(const glm::mat4 matrix, QStandardItem* parent) const
{
    QStandardItem* item = new QStandardItem("transformation");

    QString str;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            str += QString::number(matrix[i][j]) + " ";
        }
        if (i != 3) {
            str += "\n";
        }
    }
    QStandardItem* item2 = new QStandardItem(str);
    item->appendRow(item2);

    parent->appendRow(item);
}

//void Model::modelVertex(const Vertex *vertex, QStandardItem *parent) const
//{

//}

// -----------------------------------------------------------------------
//    static Assimp::Importer m_importer;
/*  Functions   */
// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::assimpLoadModel(std::string const& path)
{

    //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << m_fun;
    //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();
    // read file via ASSIMP
    Assimp::Importer m_importer;
    //        qDebug() << "[MODEL] m_importer : " << &m_importer;
    const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    //    m_scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    //        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_FlipWindingOrder);
    //            const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded);
    qDebug() << "[MODEL]" << path.c_str() << "aiScene : " << scene << "importer" << &m_importer << "numMeshes" << scene->mNumMeshes;
    //        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << m_importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    QFileInfo fileInfo(path.c_str());
    m_filename = fileInfo.baseName().toStdString();

    //            std::cout << "scene:";
    //            std::cout << ", numLights: " << scene->mNumLights;
    //            std::cout << ", numMeshes: " << scene->mNumMeshes;
    //            std::cout << ", numCameras: " << scene->mNumCameras;
    //            std::cout << ", numTextures: " << scene->mNumTextures;
    //            std::cout << ", numMaterials: " << scene->mNumMaterials;
    //            std::cout << ", numAnimations: " << scene->mNumAnimations << std::endl;
    //    for (uint i =0; i <scene->mNumTextures; ++i) {

    //    }
    for (uint i = 0; i < scene->mNumMaterials; ++i) {
        //        const aiMaterial * scene->mMaterials[i];
        aiMaterial* ai_material = scene->mMaterials[i];

        aiString ai_name;
        ai_material->Get(AI_MATKEY_NAME, ai_name);
        Material material(ai_name.C_Str());
        //        qDebug() << ai_name.C_Str();
        aiColor3D ai_ambient;
        ai_material->Get(AI_MATKEY_COLOR_AMBIENT, ai_ambient);
        material.m_colorAmbient = aiColor3ToGlm(ai_ambient);

        aiColor3D ai_diffuse;
        ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_diffuse);
//        qDebug() << ai_diffuse.b << ai_diffuse.g << ai_diffuse.r;
        material.m_colorDiffuse = aiColor3ToGlm(ai_diffuse);

        aiColor3D ai_specular;
        ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_specular);
        material.m_colorSpecular = aiColor3ToGlm(ai_specular);


//        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;
//        float ai_shininess;
        ai_material->Get(AI_MATKEY_SHININESS, material.m_shininess);
//        material.m_shininess = ai_shininess;
//        aiColor3D ai_emissive;
//        aiColor3D ai_transparent;




        // 1. diffuse maps
        //        std::vector<uint> textures;
        material.m_textures[Texture::e_type::diffuse] = assimpLoadMaterialTextures(ai_material, aiTextureType_DIFFUSE, Texture::e_type::diffuse);
        //        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        material.m_textures[Texture::e_type::specular] = assimpLoadMaterialTextures(ai_material, aiTextureType_SPECULAR, Texture::e_type::specular);
        //        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        material.m_textures[Texture::e_type::normal] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::e_type::normal);
        //        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        material.m_textures[Texture::e_type::height] = assimpLoadMaterialTextures(ai_material, aiTextureType_HEIGHT, Texture::e_type::height);
        //        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        m_materials.push_back(std::move(material));
    }

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* ai_mesh = scene->mMeshes[i];
        m_meshes.push_back(assimpProcessMesh(ai_mesh, scene, 0));
    }

    //    for (int i =0; i <scene->mNumTextures; ++i) {

    //    }

    // process ASSIMP's root node recursively
    //    m_rootNode = scene->mRootNode;

    //    processNode(scene->mRootNode, scene, 0);
    m_rootNode = assimpProcessNode(scene->mRootNode, scene, 0);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
Node* Model::assimpProcessNode(aiNode* node, const aiScene* scene, int depth)
{
    Node* newNode = new Node(node->mName.C_Str());

    //            for (int i = 0; i < depth; ++i) {
    //                std::cout << "\t";
    //            }
    //            std::cout << "node: " << node->mName.C_Str();
    //            std::cout << ", numMeshes: " << node->mNumMeshes;
    //            std::cout << ", numChildren: " << node->mNumChildren;
    //            std::cout << std::endl;

    newNode->m_numMeshes = node->mNumMeshes;
    newNode->m_meshes.resize(newNode->m_numMeshes);
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        //        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //        newNode->m_meshes.push_back(1);
        //        m_meshes.push_back(assimpProcessMesh(mesh, scene, depth + 1));

        //        newNode->m_meshes[i] = m_meshes.size() - 1;
        newNode->m_meshes[i] = node->mMeshes[i];
        //        newNode->m_meshes.push_back(&m_meshes.back());
        //        newNode->m_transformation = node->mTransformation
    }
    // after we've processed all of the m_meshes (if any) we then recursively process each of the children nodes
    newNode->m_numChildren = node->mNumChildren;
    newNode->m_children.resize(newNode->m_numChildren);
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        newNode->m_children[i] = assimpProcessNode(node->mChildren[i], scene, depth + 1);
    }

    newNode->m_transformation = aiMatrix4x4ToGlm(node->mTransformation);

    return newNode;
}

Mesh Model::assimpProcessMesh(const aiMesh* ai_mesh, const aiScene* scene, int depth)
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
    Mesh mesh(ai_mesh->mName.C_Str());
    mesh.m_numFaces = ai_mesh->mNumFaces;
    mesh.m_material = ai_mesh->mMaterialIndex;

    for (int i = 0; i < ai_mesh->mNumFaces; ++i) {
        aiFace* ai_face = &ai_mesh->mFaces[i];
        //        Face face;
        //        Q_ASSERT(ai_face->mNumIndices == 3);
        //        mesh.m_lenFaces.push_back(ai_face->mNumIndices);

        for (int j = 0; j < ai_face->mNumIndices; ++j) {
            uint indice = ai_face->mIndices[j];
            //            face.m_indices.push_back(indice);
            mesh.m_indices.push_back(indice);
        }
        //        mesh.m_faces.push_back(face);
    }

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

        mesh.m_vertices.push_back(std::move(v));
    }

    mesh.setupMesh();
    return std::move(mesh);

    //    // data to fill
    //    std::vector<Vertex> vertices;
    //    std::vector<unsigned int> indices;
    //    std::vector<Texture> textures;

    //    // Walk through each of the mesh's vertices
    //    for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
    //        Vertex vertex;
    //        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
    //        // positions
    //        vector.x = ai_mesh->mVertices[i].x;
    //        vector.y = ai_mesh->mVertices[i].y;
    //        vector.z = ai_mesh->mVertices[i].z;
    //        vertex.Position = vector;
    //        // normals
    //        if (!ai_mesh->HasNormals()) {
    //            vector = glm::vec3(0.0);
    //        } else {
    //            vector.x = ai_mesh->mNormals[i].x;
    //            vector.y = ai_mesh->mNormals[i].y;
    //            vector.z = ai_mesh->mNormals[i].z;
    //        }
    //        vertex.Normal = vector;
    //        // texture coordinates
    //        if (ai_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
    //        {
    //            glm::vec2 vec;
    //            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
    //            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
    //            vec.x = ai_mesh->mTextureCoords[0][i].x;
    //            vec.y = ai_mesh->mTextureCoords[0][i].y;
    //            vertex.TexCoords = vec;
    //        } else
    //            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

    //        if (ai_mesh->HasTangentsAndBitangents()) {
    //            // tangent
    //            vector.x = ai_mesh->mTangents[i].x;
    //            vector.y = ai_mesh->mTangents[i].y;
    //            vector.z = ai_mesh->mTangents[i].z;
    //            vertex.Tangent = vector;
    //            // bitangent
    //            vector.x = ai_mesh->mBitangents[i].x;
    //            vector.y = ai_mesh->mBitangents[i].y;
    //            vector.z = ai_mesh->mBitangents[i].z;
    //            vertex.Bitangent = vector;
    //        }
    //        vertices.push_back(vertex);
    //    }
    //    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    //    for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
    //        aiFace face = ai_mesh->mFaces[i];
    //        // retrieve all indices of the face and store them in the indices vector
    //        for (unsigned int j = 0; j < face.mNumIndices; j++)
    //            indices.push_back(face.mIndices[j]);
    //    }
    //    // process materials
    //        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
    //    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    //    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    //    // Same applies to other texture as the following list summarizes:
    //    // diffuse: texture_diffuseN
    //    // specular: texture_specularN
    //    // normal: texture_normalN

    //    // 1. diffuse maps
    //    std::vector<Texture> diffuseMaps = assimpLoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //    // 2. specular maps
    //    std::vector<Texture> specularMaps = assimpLoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //    // 3. normal maps
    //    std::vector<Texture> normalMaps = assimpLoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //    // 4. height maps
    //    std::vector<Texture> heightMaps = assimpLoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    //    // return a mesh object created from the extracted mesh data
    //    mesh.vertices = vertices;
    //    mesh.indices = indices;
    //    mesh.textures = textures;

    //    mesh.setupMesh();
    //    //    return Mesh(ai_mesh->mName.C_Str(), vertices, indices, textures);
    //    return std::move(mesh);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<uint> Model::assimpLoadMaterialTextures(aiMaterial* mat, aiTextureType ai_type, Texture::e_type type)
{
    //    std::vector<Texture> textures;
    std::vector<uint> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(ai_type); i++) {
        //        qDebug() << "has textures";
        aiString str;
        mat->GetTexture(ai_type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < m_textures.size(); j++) {
            if (std::strcmp(m_textures[j].path.data(), str.C_Str()) == 0) {
                //                textures.push_back(m_textures[j]);
                textures.push_back(j);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip) { // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = type;
            texture.path = this->directory + "/" + str.C_Str();
            bool success;
            QImage image = loadTga(texture.path.c_str(), success);
            Q_ASSERT(success);
//            Q_ASSERT(! image.isNull());
//            QPixmap pixmap(image);
//            QPixmap pixmap(QPixmap::fromImage(image));
            texture.pixmap = QPixmap::fromImage(image);
            //            textures.push_back(texture);
            textures.push_back(m_textures.size());
            m_textures.push_back(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

//    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false)
unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{
    std::string filename = std::string(path);
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

std::string Model::filename() const
{
    return m_filename;
}
