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
    void addModel(std::string file);

    void load(std::ifstream & file);
    void save(std::ofstream & file);

private:
    void clear();

private:
//    std::vector<std::string> m_modelPaths;
    QStandardItemModel m_itemModel;
    std::vector<Model> m_models;

    Model* m_camera;
    Grid * m_grid;

    Shader* m_shaderCamera;
    Shader* m_shader;

public:
    QStandardItemModel* itemModel();
};

//static Scene g_scene;

#endif // SCENE_H
