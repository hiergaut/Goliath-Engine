#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <QString>
#include <glm/glm.hpp>

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
    operator QString() const {
        std::string str = "";
        str += std::to_string(Position.x) + " " + std::to_string(Position.y) + " " + std::to_string(Position.z) + " ";
        str += std::to_string(Normal.x) + " " + std::to_string(Normal.y)+ " "  + std::to_string(Normal.z)+ " " ;
        str += std::to_string(TexCoords.x)+ " "  + std::to_string(TexCoords.y);
//        return "fuck";
        return str.c_str();
    }
};

//using NUM_BONES_PER_VEREX = 4;

struct VertexBoneData {
    uint IDs[4];
    float Weights[4];
};


#endif // VERTEX_H
