#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

//#include <map>
#include <QMap>
#include <QString>
//#include <list>
#include <QDebug>

#include <gui/QSplitterNode.h>
#include <fstream>

class Environment
{
public:
//    std::map<std::string, std::list<int>> m_sizes;
//    QMap<QString, QList<int>> m_sizes;
    std::vector<QSplitterNode> m_SplitterNodes;
    int m_iSplitterNode;

public:
    Environment();

    void clear() {
//        m_sizes.clear();
        m_SplitterNodes.clear();
    }

    void save(std::ofstream & file) {
//        file.write(&m_sizesBytes, sizeof(m_sizesBytes));
//        long bytes;
        size_t size;
//        bytes = str.size() * sizeof(char);
//        qDebug() << "write " << bytes << " bytes";
        size = m_SplitterNodes.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto & node : m_SplitterNodes) {
            node.save(file);
        }

//        file.write(reinterpret_cast<const char *>(str.data()), size);


    }

    void load(std::ifstream & file) {
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
//        qDebug() << "read " << size << " size";
        m_SplitterNodes.clear();
        m_SplitterNodes = std::vector<QSplitterNode>(size);
        m_iSplitterNode = 0;
        for (auto & node : m_SplitterNodes) {
            node.load(file);
        }
//        for (int i =0; i <size; ++i) {
//            file.read(reinterpret_cast<char*>(&size), sizeof(size));
//            m_SplitterNodes.load(file);
//        }
    }

    friend std::ostream & operator << (std::ostream & out, const Environment & env) {
        int i =0;
        out << "[ENV] nb nodes : " << env.m_SplitterNodes.size() << std::endl;
        for (const auto & node : env.m_SplitterNodes) {
            out << "[ENV] node " << ++i << ": " << node << std::endl;
        }
        return out;
    }

private:
//    size_t m_sizesBytes;
};

extern Environment g_env;

#endif // ENVIRONMENT_H
