#ifndef SESSIONSAVE_H
#define SESSIONSAVE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <map>
#include <vector>
#include <iostream>

class SessionSave {
public:
    //    SessionSave();
    template <class T>
    static void save(const T& val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
        std::cout << "save" << std::endl;
    }

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
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

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

    static void save(const glm::mat4& mat, std::ofstream& file)
    {
        float data[16];
        std::memcpy(data, (const float *)glm::value_ptr(mat), 16 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const glm::quat& quaternion, std::ofstream& file)
    {
        float data[4];
        std::memcpy(data, glm::value_ptr(quaternion), 4 * sizeof(float));

        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const std::string& str, std::ofstream& file)
    {
        //        float data[3];
        //        file.read(reinterpret_cast<char*>(&data), sizeof(data));
        uint size = str.size();

        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        //    char data[size];
        //        str.resize(size);
        file.write(reinterpret_cast<const char*>(str.data()), sizeof(str.data()));
        //        return glm::make_vec3(data);
        //        vec = glm::make_vec3(data);
    }

    static void save(const float& val, std::ofstream& file)
    {
        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
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
};

#endif // SESSIONSAVE_H
