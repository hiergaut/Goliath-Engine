#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

//#include <engine/scene/model/Model.h>
//#include "../ParamModel.h"
//#include <engine/scene/model/Vertex.h>
#include "../../Model.h"

class BSplineSurface : public Model {
    //public:
    //    BSplineSurface();
public:
    static const uint m_nbLine = 5;
    static const uint m_nbCol = 6;
    static const uint g_maxLenKnots = 13;
//    = 13;

    uint m_k[2];
    uint m_dotPerEdge[2];
    //    std::vector<float> m_knots[2];
    float m_knots[2][g_maxLenKnots];
    //    std::vector<glm::vec3> m_controlPoints;
    glm::vec3 m_controlPoints[m_nbLine][m_nbCol];
    //    std::vector<bool> m_selected;
    bool m_selected[m_nbLine][m_nbCol];
    //    std::vector<glm::vec3> m_memControlPoints;

public:
    BSplineSurface();
    BSplineSurface(std::ifstream& file);
    //    BSplineSurface(BSplineSurface && splineCurve) noexcept = default;

    ~BSplineSurface() override;

    void setupGL();

    std::string name() const override;

    void setUk(uint k);
    void setVk(uint k);
    void setUDotPerEdge(uint dotPerEdge);
    void setVDotPerEdge(uint dotPerEdge);
    //    void updateCurve();
    void updateSurface(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));
    void drawSelected(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
    void updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform) override;
    void vertexSelectRay(const Ray& ray, bool additional);

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

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::uvec3> m_indiceTriangles;
    uint m_vao2;
    uint m_vbo2;
    uint m_nbo2;
    uint m_ebo2;

    //    uint m_accuracy;
};

#endif // BSPLINESURFACE_H
