#include "Bone.h"

Bone::Bone(const aiBone* ai_bone)
    : m_name(ai_bone->mName.C_Str())
{
}

Bone::~Bone()
{
    std::cout << "\033[31m";
    std::cout << "[BONE] '" << m_name << "' destruct " << this << std::endl;
    std::cout << "\033[0m";


}
