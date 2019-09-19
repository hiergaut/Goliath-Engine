#ifndef PARAMMODEL_H
#define PARAMMODEL_H

#include <engine/scene/model/Model.h>
#include <engine/scene/model/Vertex.h>

class ParamModel: public Model
{
public:
    ParamModel();
    ParamModel(std::ifstream & file);

    void setupGL();

protected:
    void save(std::ofstream &file) const override;

    void prepareHierarchy(ulong frameTime) const override;
    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;

    void updateBoundingBox() const override;
    void drawBoundingBox(const Shader &shader) const override;

    std::string name() const override;
    void buildItemModel(QStandardItem *parent) const override;

private:
    QOpenGLFunctionsCore * m_fun = nullptr;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::uvec2> m_indices;

    uint m_vbo;
    uint m_ebo;
    uint m_vao;


};

#endif // PARAMMODEL_H
