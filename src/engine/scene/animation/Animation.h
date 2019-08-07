#ifndef ANIMATION_H
#define ANIMATION_H

#include <assimp/scene.h>

class Animation
{
public:
    std::string m_name;

public:
    Animation(const aiAnimation * ai_animation);

private:
};

#endif // ANIMATION_H
