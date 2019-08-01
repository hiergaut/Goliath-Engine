#ifndef SCENE_H
#define SCENE_H

#include <QStandardItemModel>
#include <opengl/model.h>
#include <opengl/shader.h>
#include <opengl/grid.h>

class Scene {
public:
    Scene();
    //    QStandardItemModel *model() const;

    //    class iterator {
    //    public:
    //        iterator(const Scene & scene);

    //    private:

    //    };
    void initialize();

    //    const_it begin() const {
    ////        return iterator(*this);
    //        return m_models.begin();
    //    }
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    QStandardItemModel* itemModel();

private:
    QStandardItemModel m_itemModel;

    std::vector<Model> m_models;

    Model* m_camera;
    Grid * m_grid;

    Shader* m_shaderCamera;
    Shader* m_shader;
};

//static Scene g_scene;

#endif // SCENE_H
