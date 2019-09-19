#ifndef VERTEX_H
#define VERTEX_H

#include <QString>
#include <glm/glm.hpp>
#include <iostream>
#include <session/Session.h>

#include <opengl/rayTracer/Ray.h>

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    //    glm::vec3 Tangent;
    // bitangent
    //    glm::vec3 Bitangent;
    operator QString() const
    {
        std::string str = "";
        str += std::to_string(Position.x) + " " + std::to_string(Position.y) + " " + std::to_string(Position.z) + " ";
        str += std::to_string(Normal.x) + " " + std::to_string(Normal.y) + " " + std::to_string(Normal.z) + " ";
        str += std::to_string(TexCoords.x) + " " + std::to_string(TexCoords.y);
        //        return "fuck";
        return str.c_str();
    }

    Vertex() {

    }

    Vertex(std::ifstream& file)
    {
        Session::load(Position, file);
        Session::load(Normal, file);
        Session::load(TexCoords, file);
    }

    void save(std::ofstream& file) const
    {
        Session::save(Position, file);
        Session::save(Normal, file);
        Session::save(TexCoords, file);
    }

//    bool intersect(const Ray & ray, float & depth) const {

//    }
};

//using NUM_BONES_PER_VEREX = 4;

struct VertexBoneData {
    uint IDs[4];
    float Weights[4];

    VertexBoneData() :
        IDs{0}
      , Weights{0}
    {
    }


    VertexBoneData(std::ifstream& file)
    {
        for (uint i = 0; i < 4; ++i) {
            Session::load(IDs[i], file);
            Session::load(Weights[i], file);
        }
    }

    void save(std::ofstream& file) const
    {
        for (uint i = 0; i < 4; ++i) {
            Session::save(IDs[i], file);
            Session::save(Weights[i], file);
        }
    }
};

#endif // VERTEX_H
