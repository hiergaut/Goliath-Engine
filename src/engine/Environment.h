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

class Environment
{
public:
//    std::map<std::string, std::list<int>> m_sizes;
//    QMap<QString, QList<int>> m_sizes;
//    std::vector<QSplitterNode> m_SplitterNodes;
//    int m_iSplitterNode;
    QSplitterNode ** m_splitterRoot;
    QSettings m_settings;

    std::vector<Model> m_scene;



public:
    Environment();

//    void clear();
    void save(std::ofstream & file);
    void load(std::ifstream & file);
//    friend std::ostream & operator << (std::ostream & out, const Environment & env);

private:
//    size_t m_sizesBytes;
};

extern Environment g_env;

#endif // ENVIRONMENT_H
