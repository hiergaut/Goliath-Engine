#ifndef SESSIONLOAD_H
#define SESSIONLOAD_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assert.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class SessionLoad {
public:
    //    SessionLoad();
    // --------------------------- BASIC TYPE
    //    template<class T>
    //    static void load(T& val, std::ifstream& file) {
    //        file.read(reinterpret_cast<char *>(&val), sizeof(val));
    //        std::cout << "load" << std::endl;
    //    }
    static void load(uint& val, std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&val), sizeof(uint));
        //    std::cout << "\033[31m";
//                std::cout << "load uint " << val << std::endl;
        //    std::cout << "\033[0m";
    }
    static void load(float& val, std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&val), sizeof(float));
//        std::cout << "\033[31m";
//        std::cout << "load float " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void load(double& val, std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&val), sizeof(double));
//        std::cout << "\033[31m";
//        std::cout << "load double " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void load(bool& val, std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&val), sizeof(bool));
//        std::cout << "\033[31m";
//        std::cout << "load bool " << val << std::endl;
//        std::cout << "\033[0m";
    }
    static void load(int& val, std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&val), sizeof(val));
    }

    template <class T, class U>
    static void load(std::pair<T, U>& pair, std::ifstream& file)
    {
        T t;
        load(t, file);
        U u;
        load(u, file);

        pair = std::make_pair(t, u);
    }

    template <class T>
    static void load(std::vector<T>& vec, std::ifstream& file)
    {
        assert(vec.empty());

        uint size;
        //        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        load(size, file);

        //        Session::load()
        for (uint j = 0; j < size; j++) {
            T val;
            //            file.read(reinterpret_cast<char*>(&val), sizeof(val));
            load(val, file);
            //            m_iTextures[i].emplace_back(val);
            vec.emplace_back(val);
        }
    }

    template <class T, class U>
    static void load(std::map<T, U>& map, std::ifstream& file)
    {
        assert(map.empty());

        uint size;
        load(size, file);

        for (uint i = 0; i < size; ++i) {
            T t;
            load(t, file);
            U u;
            load(u, file);

            map.insert(std::make_pair(t, u));
        }
    }

    static void load(glm::vec3& vec, std::ifstream& file)
    {
        float data[3];
        file.read(reinterpret_cast<char*>(&data), sizeof(data));

        //        return glm::make_vec3(data);
        vec = glm::make_vec3(data);
    }

    static void load(glm::vec2& vec, std::ifstream& file)
    {
        float data[2];
        file.read(reinterpret_cast<char*>(&data), sizeof(data));

        //        return glm::make_vec3(data);
        vec = glm::make_vec2(data);
    }

    static void load(glm::uvec2 & vec, std::ifstream & file) {
        float data[2];
        file.read(reinterpret_cast<char*>(&data), sizeof(data));

        vec = glm::make_vec2(data);
    }

//    static void load(const glm::mat4& mat, std::ifstream& file)
//    {
//        float data[16];
//        file.read(reinterpret_cast<char*>(&data), sizeof(data));

//        //        return glm::make_vec3(data);
//        mat = glm::make_mat4(data);
//    }
    static void load(glm::mat4 mat, std::ifstream& file)
    {
        float data[16];
        file.read(reinterpret_cast<char*>(&data), sizeof(data));

        //        return glm::make_vec3(data);
        mat = glm::make_mat4(data);
    }


    static void load(glm::quat & quaternion, std::ifstream& file)
    {
        float data[4];
        file.read(reinterpret_cast<char*>(&data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
//        quaternion = glm::make_quat(data);

        quaternion = glm::quat(data[0], data[1], data[2], data[3]);
//        quaternion = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
    }

    static void load(std::string& str, std::ifstream& file)
    {
        assert(str.empty());
        //        float data[3];
        //        file.read(reinterpret_cast<char*>(&data), sizeof(data));
        uint size;
        load(size, file);

        //        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        //    char data[size];
        str.resize(size);
        file.read(const_cast<char*>(str.data()), size * sizeof(char));
        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
//        std::cout << "\033[31m";
//        std::cout << "load string '" << str << "'" << std::endl;
//        std::cout << "\033[0m";
    }

    //    static glm::vec3 load(int & val, std::ifstream & file) {
    //        float data[3];
    //        file.read(reinterpret_cast<char*>(&data), sizeof(data));

    ////        return glm::make_vec3(data);
    ////        vec = glm::make_vec3(data);
    //    }

    static int loadEnum(std::ifstream& file)
    {
        int id;
        file.read(reinterpret_cast<char*>(&id), sizeof(id));

        return id;
    }

    static void load(glm::vec3 *  tab, uint len, std::ifstream & file) {
//        glm::vec3 t[len];
        file.read(reinterpret_cast<char*>(tab), len * sizeof(glm::vec3));

//        tab = t;
    }

    static void load(uint *  tab, uint len, std::ifstream & file) {
//        glm::vec3 t[len];
        file.read(reinterpret_cast<char*>(tab), len * sizeof(uint));

//        tab = t;
    }

    static void load(float *  tab, uint len, std::ifstream & file) {
//        glm::vec3 t[len];
        file.read(reinterpret_cast<char*>(tab), len * sizeof(float));

//        tab = t;
    }
    static void load(bool *  tab, uint len, std::ifstream & file) {
//        glm::vec3 t[len];
        file.read(reinterpret_cast<char*>(tab), len * sizeof(bool));

//        tab = t;
    }
};

#endif // SESSIONLOAD_H
