#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

//#include <engine/scene/model/Model.h>
//#include "../ParamModel.h"
//#include <engine/scene/model/Vertex.h>
#include "../../Model.h"
#include <opengl/Frustum.h>

class BSplineCurve : public Model {
    //public:
    //    BSplineCurve();
public:
    static const uint g_maxLenKnots = 20;

    uint m_k = 3;
    uint m_dotPerEdge = 10;
//    std::vector<float> m_knots;
    float m_knots[g_maxLenKnots];
    std::vector<glm::vec3> m_controlPoints;
    std::vector<bool> m_selected;
    bool m_periodic = false;
    //    std::vector<glm::vec3> m_memControlPoints;

    enum Type {
        SPLINE,
        CIRCLE,
        CIRCLE8,
    };

public:
    BSplineCurve(Type type);
    BSplineCurve(std::ifstream& file);
//    BSplineCurve(BSplineCurve && splineCurve) noexcept = default;

    ~BSplineCurve() override;

    void setupGL();

    const std::string name() const override;

    void setK(uint k);
    void setDotPerEdge(uint dotPerEdge);
    //    void updateCurve();
    void updateCurve(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));
    void drawSelected(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
    void updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform) override;
    void vertexSelectRay(const Ray &ray, bool additional);
//    void vertexSelectFrustum(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix, bool additional = false);
    void vertexSelectFrustum(const Frustum & frustum, bool additional = false);

    void clampStart();
    void clampEnd();
    void setUniform();

protected:
    void save(std::ofstream& file) const override;

    void prepareHierarchy(ulong frameTime) const override;
    void draw(const Shader& shader, bool dotCloud, const Frustum & frustum, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;

    void updateBoundingBox() override;
    void drawBoundingBox(const Shader& shader) const override;

    void buildItemModel(QStandardItem* parent) const override;


private:
    QOpenGLFunctionsCore* m_fun = nullptr;
        std::vector<glm::uvec2> m_indices;
    uint m_vbo;
        uint m_ebo;
    uint m_vao;

    std::vector<glm::vec3> m_curve;
    std::vector<glm::uvec2> m_curveIndiceLines;
    uint m_vao2;
    uint m_vbo2;
    uint m_ebo2;

    //    uint m_accuracy;
};

#endif // BSPLINECURVE_H
