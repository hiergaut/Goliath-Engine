#include "RayTracer.h"

Scene * RayTracer::m_scene = nullptr;
//BoneGeometry * RayTracer::m_bone= nullptr;
//std::vector<Ray> RayTracer::m_rays;

//RayTracer::RayTracer(glm::vec3 source, glm::vec3 direction)
//{

//}

//void RayTracer::launch(const Ray &ray)
//{
//    Q_ASSERT(m_scene != nullptr);

//    m_scene->objectFinderRay(ray);
////    m_rays.push_back(ray);
//}

void RayTracer::selectRay(const Ray &ray)
{
    Q_ASSERT(m_scene != nullptr);

    m_scene->selectRay(ray);
}

//void RayTracer::unselectRay(const Ray &ray)
//{
//    Q_ASSERT(m_scene != nullptr);

//    m_scene->unselectRay(ray);
//}

void RayTracer::setScene(Scene *scene)
{
    m_scene = scene;
}

//void RayTracer::draw(const glm::mat4 &modelMatrix, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
//{
//    for (const Ray & ray : m_rays) {
//        m_bone->drawLine(modelMatrix, ray.m_source, ray.m_source + ray.m_direction * 1000.0f);
//    }

//}

//void RayTracer::setBone(BoneGeometry *bone)
//{
//    m_bone = bone;
//}
