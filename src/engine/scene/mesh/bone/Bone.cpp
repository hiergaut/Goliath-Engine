#include "Bone.h"

Bone::Bone(const aiBone* ai_bone)
    : m_name(ai_bone->mName.C_Str())
{
}
