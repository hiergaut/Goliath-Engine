#ifndef PARAMMODEL_H
#define PARAMMODEL_H

//#include <engine/scene/model/Model.h>
//#include <engine/scene/model/Vertex.h>

//class ParamModel : public Model {
//public:
//    enum Type {
//        BSPLINE_CURVE,
//        BSPLINE_SURFACE,
//    } m_type;
//    //    uint m_accuracy;

//        ParamModel(ParamModel::Type type);
//    ParamModel(std::ifstream& file);

//    //    void save(std::ofstream & file);
//    //    static ParamModel * load(std::ifstream & file);

////    void drawSelected
//    virtual void drawSelected(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
//    virtual void vertexSelectRay(const Ray & ray, bool additional);


//    void prepareHierarchy(ulong frameTime) const override;
//    void draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
//    void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;

//    void updateBoundingBox() const override;
//    void drawBoundingBox(const Shader& shader) const override;

//    void buildItemModel(QStandardItem* parent) const override;

//    void updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform) override;
//    std::string name() const override;
//};

#endif // PARAMMODEL_H
