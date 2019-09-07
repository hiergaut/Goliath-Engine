#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <engine/Scene.h>
#include "Ray.h"

#include <opengl/camera/CameraWorld.h>

class RayTracer
{
public:
//    RayTracer(glm::vec3 source, glm::vec3 direction);
//    static void launch(const Ray & ray);
//    void findFirstObject(glm::vec3 source, glm::vec3 direction);

    static void selectRay(const Ray & ray, bool additional = false);
//    static void unselectRay(const Ray & ray);
    static void setSelectRootTransform(const glm::mat4 & transformMatrix, const glm::mat4 &worldTransform);
    static void setSelectToOriginTransform();

    static void setSelectFocus(CameraWorld & camera);
    static void deleteSelected();


    static void setScene(Scene *scene);

//    static void draw(const glm::mat4 & modelMatrix, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);

//    static void setBone(BoneGeometry *bone);

private:
    static Scene * m_scene;

//    static BoneGeometry * m_bone;
//    static std::vector<Ray> m_rays;

};

#endif // RAYTRACER_H
