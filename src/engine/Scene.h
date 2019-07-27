#ifndef SCENE_H
#define SCENE_H

#include <QStandardItemModel>

class Scene
{
public:
    Scene();
    QStandardItemModel *model() const;

private:

    QStandardItemModel * m_model;
};

static Scene g_scene;

#endif // SCENE_H
