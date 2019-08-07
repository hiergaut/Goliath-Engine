#include "Animation.h"

Animation::Animation(const aiAnimation* ai_animation)
    : m_name(ai_animation->mName.C_Str())
{
}
