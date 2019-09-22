#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

//#include <engine/scene/model/Model.h>
//#include "../ParamModel.h"
//#include <engine/scene/model/Vertex.h>
#include "../../Model.h"

class BSplineCurve : public Model {
    //public:
    //    BSplineCurve();
public:
    uint m_k;
    uint m_dotPerEdge;
    std::vector<float> m_knots;
    std::vector<glm::vec3> m_controlPoints;
    std::vector<bool> m_selected;
    //    std::vector<glm::vec3> m_memControlPoints;

public:
    BSplineCurve();
    BSplineCurve(std::ifstream& file);
//    BSplineCurve(BSplineCurve && splineCurve) noexcept = default;

    ~BSplineCurve() override;

    void setupGL();

    std::string name() const override;

    void setK(uint k);
    void setDotPerEdge(uint dotPerEdge);
    //    void updateCurve();
    void updateCurve(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));
    void drawSelected(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
    void updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform) override;
    void vertexSelectRay(const Ray &ray, bool additional);

protected:
    void save(std::ofstream& file) const override;

    void prepareHierarchy(ulong frameTime) const override;
    void draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;

    void updateBoundingBox() const override;
    void drawBoundingBox(const Shader& shader) const override;

    void buildItemModel(QStandardItem* parent) const override;

private:
    QOpenGLFunctionsCore* m_fun = nullptr;
    //    std::vector<glm::uvec2> m_indices;
    uint m_vbo;
    //    uint m_ebo;
    uint m_vao;

    std::vector<glm::vec3> m_curve;
    std::vector<glm::uvec2> m_curveIndiceLines;
    uint m_vao2;
    uint m_vbo2;
    uint m_ebo2;

    //    uint m_accuracy;
};

#endif // BSPLINECURVE_H
