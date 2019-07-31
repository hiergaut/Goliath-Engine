#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

//#include <map>
#include <QMap>
#include <QString>
//#include <list>
#include <QDebug>

#include <gui/QSplitterNode.h>
#include <fstream>
#include <QSettings>
#include <opengl/model.h>
#include <gui/editor/3dview/QOpenGLWidget_3dView.h>

class Environment
{
public:
    QSettings m_settings;
    QSplitterNode ** m_splitterRoot;

    std::vector<const QOpenGLWidget_3dView *> * m_views;
//    std::map<std::string, std::list<int>> m_sizes;
//    QMap<QString, QList<int>> m_sizes;
//    std::vector<QSplitterNode> m_SplitterNodes;
//    int m_iSplitterNode;


public:
    Environment();

//    void clear();
    void save(std::ofstream & file);
    void load(std::ifstream & file);
//    friend std::ostream & operator << (std::ostream & out, const Environment & env);
//    void addModel(std::string file);
//    void add3dView(QOpenGLWidget_3dView * view);

private:

//    std::vector<Model> m_scene;
//    std::vector<std::string> m_models;
//    std::vector<QOpenGLWidget_3dView*> m_3dViews;

//    size_t m_sizesBytes;
};

extern Environment g_env;

#endif // ENVIRONMENT_H
