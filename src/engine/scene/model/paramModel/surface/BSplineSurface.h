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
//    uint m_nbLine;
//    uint m_nbCol;
    uint m_nbCtrlPoints[2];
    static const uint g_maxLenKnots = 16;
    static const uint g_maxSize = 20;
    //    = 13;

    uint m_k[2] = { 3, 3 };
    uint m_dotPerEdge[2] = { 10, 10 };
    //    std::vector<float> m_knots[2];
    float m_knots[2][g_maxLenKnots];
    //    std::vector<glm::vec3> m_controlPoints;
    glm::vec3 m_controlPoints[g_maxSize][g_maxSize];
    //    std::vector<bool> m_selected;
    bool m_selected[g_maxSize][g_maxSize];
    //    std::vector<glm::vec3> m_memControlPoints;
    bool m_periodic[2] = {false, false};

    enum Type {
        SPHERE,
        TOMB,
        PLANE,
        THOR,
        POT,
    };
    Texture m_texture;

public:
    BSplineSurface(Type type);
    BSplineSurface(std::ifstream& file);
    //    BSplineSurface(BSplineSurface && splineCurve) noexcept = default;

    ~BSplineSurface() override;

    void setupGL();
    void setUniform(uint uv);
    static glm::vec3 deBoor(float u, uint m, const uint k, const float knots[], const std::vector<glm::vec3>& controlPoints);
    static std::vector<glm::vec3> calcCurve(const std::vector<glm::vec3>& ptsCtrl, const uint k, const uint dotPerEdge, const float knots[]);

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

    void clamp(uint i, bool start = true);
    void uSetUniform();
    void vSetUniform();
    void uClampStart();
    void uClampEnd();
    void vClampStart();
    void vClampEnd();

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
        std::vector<glm::uvec2> m_indices;
    uint m_vbo;
        uint m_ebo;
    uint m_vao;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::uvec3> m_indiceTriangles;
    std::vector<glm::vec2> m_textures;
    uint m_vao2;
    uint m_vbo2;
    uint m_nbo2;
    uint m_ebo2;
    uint m_tbo2;

    //    uint m_accuracy;
};

#endif // BSPLINESURFACE_H
