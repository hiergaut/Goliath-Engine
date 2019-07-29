#include "Environment.h"

Environment g_env;

Environment::Environment() : m_settings("Goliath", "Goliath-Engine")
{
//    m_settings.beginGroup()

}
//void Environment::clear()
//{
//    //        m_sizes.clear();
////    m_SplitterNodes.clear();
//}

void Environment::save(std::ofstream& file)
{
    //        file.write(&m_sizesBytes, sizeof(m_sizesBytes));
    //        long bytes;
    //    size_t size;
    //    //        bytes = str.size() * sizeof(char);
    //    //        qDebug() << "write " << bytes << " bytes";
    //    size = m_SplitterNodes.size();
    //    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    //    for (const auto& node : m_SplitterNodes) {
    //        node.save(file);
    //    }
    (*m_splitterRoot)->save(file);

    //        file.write(reinterpret_cast<const char *>(str.data()), size);
}

void Environment::load(std::ifstream& file)
{
    //    size_t size;
    //    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    //        qDebug() << "read " << size << " size";
    //    m_splitterRoot->clear();
    if (*m_splitterRoot != nullptr) {
        delete *m_splitterRoot;
    }
    *m_splitterRoot = new QSplitterNode;
    (*m_splitterRoot)->load(file);
    //    m_SplitterNodes.clear();
    //    m_SplitterNodes = std::vector<QSplitterNode>(size);
    //    m_iSplitterNode = 0;
    //    for (auto& node : m_SplitterNodes) {
    //        node.load(file);
    //    }
    //        for (int i =0; i <size; ++i) {
    //            file.read(reinterpret_cast<char*>(&size), sizeof(size));
    //            m_SplitterNodes.load(file);
    //        }
}

//std::ostream& operator<<(std::ostream& out, const Environment& env)
//{
////    int i = 0;
////    out << "[ENV] nb nodes : " << env.m_SplitterNodes.size() << std::endl;
////    for (const auto& node : env.m_SplitterNodes) {
////        out << "[ENV] node " << ++i << ": " << node << std::endl;
////    }
//    return out;
//}
