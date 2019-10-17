#ifndef SESSIONSAVE_H
#define SESSIONSAVE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class SessionSave {
public:
    //    SessionSave();
    //    template <class T>
    //    static void save(const T& val, std::ofstream& file)
    //    {
    //        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
    //        std::cout << "save" << std::endl;
    //    }
    static void save(uint val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(uint));
        //        std::cout << "save" << std::endl;
//        std::cout << "\033[32m";
//        std::cout << "save uint " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void save(float val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(float));
//        std::cout << "\033[32m";
//        std::cout << "save float " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void save(double val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(double));
//        std::cout << "\033[32m";
//        std::cout << "save double " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void save(bool val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(bool));
//        std::cout << "\033[32m";
//        std::cout << "save bool " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void save(int val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
    }
    //    static void save(float& val, std::ofstream& file)
    //    {
    //        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
    //    }

    template <class T, class U>
    static void save(const std::pair<T, U>& pair, std::ofstream& file)
    {
        const T& t = pair.first;
        save(t, file);
        const U& u = pair.second;
        save(u, file);

        //        pair = std::make_pair(t, u);
    }

    template <class T>
    static void save(const std::vector<T>& vec, std::ofstream& file)
    {

        uint size = vec.size();
//        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        save(size, file);

        //        Session::load()
        for (uint j = 0; j < size; j++) {
            const T& val = vec[j];
            //            file.write(reinterpret_cast<const char*>(&val), sizeof(val));

            save(val, file);
            //            m_iTextures[i].emplace_back(val);
            //            vec.emplace_back(val);
        }
    }

    template <class T, class U>
    static void save(const std::map<T, U>& map, std::ofstream& file)
    {

        uint size = map.size();
        //        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        save(size, file);

        //        Session::load()
        //        for (uint j = 0; j < size; j++) {
        for (const auto& pair : map) {
            const T& t = pair.first;
            save(t, file);

            const U& u = pair.second;
            save(u, file);

            //            const T & val = vec[j];
            //            file.write(reinterpret_cast<const char*>(&val), sizeof(val));

            //            save(val, file);
            //            m_iTextures[i].emplace_back(val);
            //            vec.emplace_back(val);
            //        }
        }
    }
    // --------------------------------------------------------------
    static void save(const glm::vec3& vec, std::ofstream& file)
    {
        float data[3];
        std::memcpy(data, glm::value_ptr(vec), 3 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const glm::vec2& vec, std::ofstream& file)
    {
        float data[2];
        std::memcpy(data, glm::value_ptr(vec), 2 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const glm::uvec2& vec, std::ofstream& file)
    {
        float data[2];
        std::memcpy(data, glm::value_ptr(vec), 2 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const glm::mat4& mat, std::ofstream& file)
    {
        float data[16];
        std::memcpy(data, (const float*)glm::value_ptr(mat), 16 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const glm::quat& quaternion, std::ofstream& file)
    {
        float data[4];
        data[0] = quaternion.w;
        data[1] = quaternion.x;
        data[2] = quaternion.y;
        data[3] = quaternion.z;
//        std::memcpy(data, glm::value_ptr(quaternion), 4 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const std::string& str, std::ofstream& file)
    {
        //        float data[3];
        //        file.read(reinterpret_cast<char*>(&data), sizeof(data));
        uint size = str.size();

//        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        save(size, file);
        //    char data[size];
        //        str.resize(size);
        file.write(reinterpret_cast<const char*>(str.data()), size * sizeof(char));
//        std::cout << "\033[32m";
//        std::cout << "save string '" << str << "'" << std::endl;
//        std::cout << "\033[0m";
        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    //    static glm::vec3 load(int & val, std::ifstream & file) {
    //        float data[3];
    //        file.read(reinterpret_cast<char*>(&data), sizeof(data));

    ////        return glm::make_vec3(data);
    ////        vec = glm::make_vec3(data);
    //    }

    static void saveEnum(int id, std::ofstream& file)
    {
        //        int id;
        file.write(reinterpret_cast<const char*>(&id), sizeof(id));

        //        return id;
    }

    static void save(const glm::vec3 * tab, uint len, std::ofstream & file) {
//        glm::vec3 t[len];
//        for (uint i =0; i <len; ++i) {
//            t[i] = tab[i];
//        }

        file.write(reinterpret_cast<const char*>(tab), len * sizeof(glm::vec3));
    }

    static void save(const uint * tab, uint len, std::ofstream & file) {
//        glm::vec3 t[len];
//        for (uint i =0; i <len; ++i) {
//            t[i] = tab[i];
//        }

        file.write(reinterpret_cast<const char*>(tab), len * sizeof(uint));
    }
    static void save(const float * tab, uint len, std::ofstream & file) {
//        glm::vec3 t[len];
//        for (uint i =0; i <len; ++i) {
//            t[i] = tab[i];
//        }

        file.write(reinterpret_cast<const char*>(tab), len * sizeof(float));
    }
    static void save(const bool * tab, uint len, std::ofstream & file) {
//        glm::vec3 t[len];
//        for (uint i =0; i <len; ++i) {
//            t[i] = tab[i];
//        }

        file.write(reinterpret_cast<const char*>(tab), len * sizeof(bool));
    }
};

#endif // SESSIONSAVE_H
