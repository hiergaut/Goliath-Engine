#ifndef BONE_H
#define BONE_H

#include <iostream>
#include <assimp/scene.h>

class Bone
{
public:
    std::string m_name;

public:
    Bone(const aiBone * ai_bone);
    ~Bone();
};

#endif // BONE_H
