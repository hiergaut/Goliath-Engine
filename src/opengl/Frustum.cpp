#include "Frustum.h"

#include <QDebug>
#include <opengl/BoundingBox.h>
#include <opengl/geometry/LineGeometry.h>

bool Frustum::m_enable = true;

Frustum::Frustum()
{
    float radius = 100.0f;
    m_ntl = glm::vec3(0.0f, 2.0f * radius, 0.0f);
    m_ntr = glm::vec3(2.0f * radius, 2.0f * radius, 0.0f);
    m_nbl = glm::vec3(0.0f, 0.0f, 0.0f);
    m_nbr = glm::vec3(2.0f * radius, 0.0f, 0.0f);

    m_ftl = glm::vec3(0.0f, radius, 2.0f * radius);
    m_ftr = glm::vec3(radius, radius, 2.0f * radius);
    m_fbl = glm::vec3(0.0f, 0.0f, 2.0f * radius);
    m_fbr = glm::vec3(radius, 0.0f, 2.0f * radius);
}

Frustum::Frustum(const glm::mat4& viewProjectionMatrix)
{
    update(viewProjectionMatrix);
    //    glm::mat4 comboMatrix = projectionMatrix * glm::transpose(viewMatrix);
    //    m_planes[TOP].set(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], -mat[3][3] + mat[3][1]);
    //    m_planes[BOTTOM].set(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], -mat[3][3] - mat[3][1]);
    //    m_planes[LEFT].set(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], -mat[3][3] - mat[3][0]);
    //    m_planes[RIGHT].set(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], -mat[3][3] + mat[3][0]);
    //    m_planes[NEAR].set(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], -mat[3][3] - mat[3][2]);
    //    m_planes[FAR].set(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], -mat[3][3] + mat[3][2]);

    //    m_planes[LEFT].set(m[])
//    for (uint i = 0; i < 4; ++i) {
//        m_planes[LEFT].m_abcd[i] = viewProjectionMatrix[3][i] + viewProjectionMatrix[0][i];
//    }
//    for (uint i = 0; i < 4; ++i) {
//        m_planes[RIGHT].m_abcd[i] = viewProjectionMatrix[3][i] - viewProjectionMatrix[0][i];
//    }

//    for (uint i = 0; i < 4; ++i) {
//        m_planes[TOP].m_abcd[i] = viewProjectionMatrix[3][i] - viewProjectionMatrix[1][i];
//    }
//    for (uint i = 0; i < 4; ++i) {
//        m_planes[BOTTOM].m_abcd[i] = viewProjectionMatrix[3][i] + viewProjectionMatrix[1][i];
//    }

//    for (uint i = 0; i < 4; ++i) {
//        m_planes[NEAR].m_abcd[i] = viewProjectionMatrix[3][i] + viewProjectionMatrix[2][i];
//    }
//    for (uint i = 0; i < 4; ++i) {
//        m_planes[FAR].m_abcd[i] = viewProjectionMatrix[3][i] - viewProjectionMatrix[2][i];
//    }
//    for (uint i = 0; i < 6; ++i) {
//        m_planes[i].normalize();
//    }
//    //    float radius = 100.0f;
//    //    m_ntl = glm::vec3(0.0f, radius, 0.0f);
//    //    m_ntr = glm::vec3(radius, radius, 0.0f);
//    //    m_nbl = glm::vec3(0.0f, 0.0f, 0.0f);
//    //    m_nbr = glm::vec3(radius, 0.0f, 0.0f);

//    //    m_ftl = glm::vec3(0.0f, radius, 2.0f * radius);
//    //    m_ftr = glm::vec3(radius, radius, 2.0f * radius);
//    //    m_fbl = glm::vec3(0.0f, 0.0f, 2.0f * radius);
//    //    m_fbr = glm::vec3(radius, 0.0f, 2.0f * radius);

////    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[NEAR], m_ntl));
////    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[NEAR], m_ntr));
////    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[NEAR], m_nbl));
////    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[NEAR], m_nbr));

////    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[FAR], m_ftl));
////    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[FAR], m_ftr));
////    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[FAR], m_fbl));
////    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[FAR], m_fbr));

////    Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[NEAR], m_ntl);
////    Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[NEAR], m_ntr);
////    Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[NEAR], m_nbl);
////    Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[NEAR], m_nbr);

////    Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[FAR], m_ftl);
////    Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[FAR], m_ftr);
////    Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[FAR], m_fbl);
////    Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[FAR], m_fbr);

//    //    // column2 + column3
//    //    m_planes[NEAR].m_a = vp[0][3] + vp[0][2];
//    //    m_planes[NEAR].m_b = vp[2][1] + vp[3][1];
//    //    m_planes[NEAR].m_c = vp[2][2] + vp[3][2];
//    //    m_planes[NEAR].m_d = vp[2][3] + vp[3][3];

//    //    // column3 - column2
//    //    m_planes[FAR].m_a = -vp[2][0] + vp[3][0];
//    //    m_planes[FAR].m_b = -vp[2][1] + vp[3][1];
//    //    m_planes[FAR].m_c = -vp[2][2] + vp[3][2];
//    //    m_planes[FAR].m_d = -vp[2][3] + vp[3][3];

//    //    // column1 + column3
//    //    m_planes[BOTTOM].m_a = vp[1][0] + vp[3][0];
//    //    m_planes[BOTTOM].m_b = vp[1][1] + vp[3][1];
//    //    m_planes[BOTTOM].m_c = vp[1][2] + vp[3][2];
//    //    m_planes[BOTTOM].m_d = vp[1][3] + vp[3][3];

//    //    // column3 - column1
//    //    m_planes[TOP].m_a = -vp[1][0] + vp[3][0];
//    //    m_planes[TOP].m_b = -vp[1][1] + vp[3][1];
//    //    m_planes[TOP].m_c = -vp[1][2] + vp[3][2];
//    //    m_planes[TOP].m_d = -vp[1][3] + vp[3][3];

//    //    // column0 + column3
//    //    m_planes[LEFT].m_a = vp[0][0] + vp[3][0];
//    //    m_planes[LEFT].m_b = vp[0][1] + vp[3][1];
//    //    m_planes[LEFT].m_c = vp[0][2] + vp[3][2];
//    //    m_planes[LEFT].m_d = vp[0][3] + vp[3][3];

//    //    // column3 - column0
//    //    m_planes[RIGHT].m_a = -vp[0][0] + vp[3][0];
//    //    m_planes[RIGHT].m_b = -vp[0][1] + vp[3][1];
//    //    m_planes[RIGHT].m_c = -vp[0][2] + vp[3][2];
//    //    m_planes[RIGHT].m_d = -vp[0][3] + vp[3][3];

//    //    m_top.normalize();
//    //    m_bottom.normalize();
//    //    m_right.normalize();
//    //    m_left.normalize();
//    //    m_planes[NEAR].normalize();
//    //    m_zFar.normalize();
//    //    for (uint i = 0; i < 6; ++i) {
//    //        m_planes[i].normalize();
    //    }
}

Frustum::Frustum(const glm::vec3& source, const glm::vec3& front,
    const glm::vec3& right, const glm::vec3& up, float zNear,
    float zFar, float fov, float ratio)
{
    //    Q_ASSERT(false);
    float halfHeightNearPlane = zNear * tanf(glm::radians(fov) * 0.5f);
    float halfWidthNearPlane = halfHeightNearPlane * ratio;
    m_ntl = source + front * zNear + up * halfHeightNearPlane + right * -halfWidthNearPlane;
    m_ntr = source + front * zNear + up * halfHeightNearPlane + right * halfWidthNearPlane;
    m_nbl = source + front * zNear + -up * halfHeightNearPlane + right * -halfWidthNearPlane;
    m_nbr = source + front * zNear + -up * halfHeightNearPlane + right * halfWidthNearPlane;

    float halfHeightFarPlane = zFar * tanf(glm::radians(fov) * 0.5f);
    float halfWidthFarPlane = halfHeightFarPlane * ratio;
    m_ftl = source + front * zFar + up * halfHeightFarPlane + right * -halfWidthFarPlane;
    m_ftr = source + front * zFar + up * halfHeightFarPlane + right * halfWidthFarPlane;
    m_fbl = source + front * zFar + -up * halfHeightFarPlane + right * -halfWidthFarPlane;
    m_fbr = source + front * zFar + -up * halfHeightFarPlane + right * halfWidthFarPlane;

    //    glm::vec3 normalPlane = glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl));
    //    float d = glm::dot(normalPlane, m_ntl);

    m_planes[TOP] = Plane(glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl)), m_ntl);
    m_planes[BOTTOM] = Plane(glm::normalize(glm::cross(m_fbl - m_nbl, m_nbr - m_nbl)), m_nbl);
    m_planes[RIGHT] = Plane(glm::normalize(glm::cross(m_nbr - m_ntr, m_ftr - m_ntr)), m_ntr);
    m_planes[LEFT] = Plane(glm::normalize(glm::cross(m_ftl - m_ntl, m_nbl - m_ntl)), m_ntl);
    m_planes[NEAR] = Plane(glm::normalize(glm::cross(m_nbl - m_ntl, m_ntr - m_ntl)), m_ntl);
    m_planes[FAR] = Plane(glm::normalize(glm::cross(m_ftr - m_ftl, m_fbl - m_ftl)), m_ftl);
    //    m_planes[FAR] = Plane(glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl)), m_ntl);

    //    for (uint i = 0; i < 6; ++i) {
    //        m_planes[i].normalize();
    //    }
}

//void Frustum::update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
void Frustum::update(const glm::mat4& viewProjectionMatrix)
{
    //    glm::mat4 comboMatrix = projectionMatrix * glm::transpose(viewMatrix);
    //    glm::mat4 comboMatrix = projectionMatrix * viewMatrix;

    //    m_planes[TOP].set(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], -mat[3][3] + mat[3][1]);
    //    m_planes[BOTTOM].set(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], -mat[3][3] - mat[3][1]);
    //    m_planes[LEFT].set(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], -mat[3][3] - mat[3][0]);
    //    m_planes[RIGHT].set(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], -mat[3][3] + mat[3][0]);
    //    m_planes[NEAR].set(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], -mat[3][3] - mat[3][2]);
    //    m_planes[FAR].set(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], -mat[3][3] + mat[3][2]);

    //    m_planes[LEFT].set(m[])
    for (uint i = 0; i < 4; ++i) {
        m_planes[LEFT].m_abcd[i] = viewProjectionMatrix[i][3] + viewProjectionMatrix[i][0];
    }
    for (uint i = 0; i < 4; ++i) {
        m_planes[RIGHT].m_abcd[i] = viewProjectionMatrix[i][3] - viewProjectionMatrix[i][0];
    }

    for (uint i = 0; i < 4; ++i) {
        m_planes[BOTTOM].m_abcd[i] = viewProjectionMatrix[i][3] + viewProjectionMatrix[i][1];
    }
    for (uint i = 0; i < 4; ++i) {
        m_planes[TOP].m_abcd[i] = viewProjectionMatrix[i][3] - viewProjectionMatrix[i][1];
    }

    for (uint i = 0; i < 4; ++i) {
        m_planes[NEAR].m_abcd[i] = viewProjectionMatrix[i][3] + viewProjectionMatrix[i][2];
    }
    for (uint i = 0; i < 4; ++i) {
        m_planes[FAR].m_abcd[i] = viewProjectionMatrix[i][3] - viewProjectionMatrix[i][2];
    }

    for (uint i = 0; i < 6; ++i) {
        m_planes[i].normalize();
    }
    //    m_planes[TOP].set(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], -mat[3][3] + mat[3][1]);
    //    m_planes[BOTTOM].set(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], -mat[3][3] - mat[3][1]);
    //    m_planes[LEFT].set(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], -mat[3][3] - mat[3][0]);
    //    m_planes[RIGHT].set(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], -mat[3][3] + mat[3][0]);
    //    m_planes[NEAR].set(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], -mat[3][3] - mat[3][2]);
    //    m_planes[FAR].set(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], -mat[3][3] + mat[3][2]);

    //    float radius = 100.0f;
    //    m_ntl = glm::vec3(0.0f, radius, 0.0f);
    //    m_ntr = glm::vec3(radius, radius, 0.0f);
    //    m_nbl = glm::vec3(0.0f, 0.0f, 0.0f);
    //    m_nbr = glm::vec3(radius, 0.0f, 0.0f);

    //    m_ftl = glm::vec3(0.0f, radius, 2.0f * radius);
    //    m_ftr = glm::vec3(radius, radius, 2.0f * radius);
    //    m_fbl = glm::vec3(0.0f, 0.0f, 2.0f * radius);
    //    m_fbr = glm::vec3(radius, 0.0f, 2.0f * radius);

//    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[NEAR], m_ntl));
//    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[NEAR], m_ntr));
//    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[NEAR], m_nbl));
//    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[NEAR], m_nbr));

//    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[FAR], m_ftl));
//    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[FAR], m_ftr));
//    Q_ASSERT(Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[FAR], m_fbl));
//    Q_ASSERT(Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[FAR], m_fbr));


    Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[NEAR], m_ntl);
    Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[NEAR], m_ntr);
    Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[NEAR], m_nbl);
    Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[NEAR], m_nbr);

    Plane::intersection(m_planes[LEFT], m_planes[TOP], m_planes[FAR], m_ftl);
    Plane::intersection(m_planes[RIGHT], m_planes[TOP], m_planes[FAR], m_ftr);
    Plane::intersection(m_planes[LEFT], m_planes[BOTTOM], m_planes[FAR], m_fbl);
    Plane::intersection(m_planes[RIGHT], m_planes[BOTTOM], m_planes[FAR], m_fbr);
}

void Frustum::draw(const Shader& shader) const
{
    shader.setBool("userColor", true);
    shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    LineGeometry::draw(m_ntl, m_ntr);
    LineGeometry::draw(m_ntr, m_nbr);
    LineGeometry::draw(m_nbr, m_nbl);
    LineGeometry::draw(m_nbl, m_ntl);

    shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    LineGeometry::draw(m_ftl, m_ftr);
    LineGeometry::draw(m_ftr, m_fbr);
    LineGeometry::draw(m_fbr, m_fbl);
    LineGeometry::draw(m_fbl, m_ftl);

    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    LineGeometry::draw(m_ntl, m_ftl);
    LineGeometry::draw(m_ntr, m_ftr);
    LineGeometry::draw(m_nbr, m_fbr);
    LineGeometry::draw(m_nbl, m_fbl);

    //    shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    //    if (!m_hits[TOP]) {
    //        LineGeometry::draw(m_ntl, 0.5f * (m_ftr + m_ftl));
    //    }
    //    if (!m_hits[BOTTOM]) {
    //        LineGeometry::draw(m_nbl, 0.5f * (m_fbr + m_fbl));
    //    }
    //    if (!m_hits[LEFT]) {
    //        LineGeometry::draw(m_nbl, 0.5f * (m_ftl + m_fbl));
    //    }
    //    if (!m_hits[RIGHT]) {
    //        LineGeometry::draw(m_nbr, 0.5f * (m_ftr + m_fbr));
    //    }
    //    if (!m_hits[NEAR]) {
    //        LineGeometry::draw(m_nbl, m_ntr);
    //    }
    //    if (!m_hits[FAR]) {
    //        LineGeometry::draw(m_fbl, m_ftr);
    //    }
    shader.setBool("userColor", false);
}

bool Frustum::encompass(const glm::vec3& vertex) const
{
    bool inside = true;
    for (uint i = 0; i < 6; ++i) {
        qDebug() << "encompass " << i << "distance " << m_planes[i].distance(vertex);
        if (m_planes[i].distance(vertex) > 0.0f) {
            inside = false;
            //            m_hits[i] = false;
            //            return false;
        } else {
            //            m_hits[i] = true;
        }
    }
    return inside;
}

bool Frustum::contains(const BoundingBox& box) const
{
    if (!m_enable)
        return true;
//    return true;
//    return m_planes[RIGHT].distance(glm::vec3(0.0f)) > 0;
//    return m_planes[BOTTOM].distance(glm::vec3(0.0f)) > 0;

    for (size_t i = 0; i < 6; ++i) {
//        if (m_planes[i].distance(box.center()) < 0) {
//            return false;
//        }
        if (m_planes[i].distance(box.getPositive(m_planes[i].normal())) < 0)
            return false;
//        if (m_planes[i].distance(box.getNegative(m_planes[i].normal())) < 0)
//            return false;
    }

    return true;
}

//void Frustum::buildFrustum(const glm::mat4 &viewProjectionMatrix)
//{

//}

//bool Frustum::cullAABB(const BoundingBox& box) const
//{
//    return false;
//    // This is where we will check all objects for culling. In this lesson, we are only culling the trees, so if the tree is culled,
//    // we will not draw it OR it's leaves. You can add other objects in your scene, and check them for culling here

//    // Initialize numTreesToDraw
//    //    numTreesToDraw = 0;

//    // Create a temporary array to get the tree instance data out
//    //    std::vector<InstanceData> tempTreeInstDat(numTrees);

//    //    bool cull = false;

//    //    // We'll start by looping through each tree
//    ////    for (int i = 0; i < numTrees; ++i) {
//    ////        cull = false;
//    //        // Loop through each frustum plane
//    ////        for (int planeID = 0; planeID < 6; ++planeID) {
//    //            for (uint i =0; i <6; ++i) {
//    //                const Plane & plane = m_planes[i];
//    //                const glm::vec3 planeNormal = plane.normal();
//    ////            XMVECTOR planeNormal = XMVectorSet(frustumPlanes[planeID].x, frustumPlanes[planeID].y, frustumPlanes[planeID].z, 0.0f);
//    //            float planeConstant = plane.m_abcd[3];

//    //            // Check each axis (x,y,z) to get the AABB vertex furthest away from the direction the plane is facing (plane normal)
//    //            glm::vec3 axisVert;

//    //            // x-axis
//    //            if (plane.m_abcd[0] < 0.0f) // Which AABB vertex is furthest down (plane normals direction) the x axis
//    //                axisVert.x = box.m_bounds[0].x + treeInstanceData[i].pos.x; // min x plus tree positions x
//    //            else
//    //                axisVert.x = treeAABB[1].x + treeInstanceData[i].pos.x; // max x plus tree positions x

//    //            // y-axis
//    //            if (m_planes[planeID].y < 0.0f) // Which AABB vertex is furthest down (plane normals direction) the y axis
//    //                axisVert.y = treeAABB[0].y + treeInstanceData[i].pos.y; // min y plus tree positions y
//    //            else
//    //                axisVert.y = treeAABB[1].y + treeInstanceData[i].pos.y; // max y plus tree positions y

//    //            // z-axis
//    //            if (m_planes[planeID].z < 0.0f) // Which AABB vertex is furthest down (plane normals direction) the z axis
//    //                axisVert.z = treeAABB[0].z + treeInstanceData[i].pos.z; // min z plus tree positions z
//    //            else
//    //                axisVert.z = treeAABB[1].z + treeInstanceData[i].pos.z; // max z plus tree positions z

//    //            // Now we get the signed distance from the AABB vertex that's furthest down the frustum planes normal,
//    //            // and if the signed distance is negative, then the entire bounding box is behind the frustum plane, which means
//    //            // that it should be culled
//    //            if (XMVectorGetX(XMVector3Dot(planeNormal, XMLoadFloat3(&axisVert))) + planeConstant < 0.0f) {
//    //                cull = true;
//    //                // Skip remaining planes to check and move on to next tree
//    //                break;
//    //            }
//    //        }

//    //        //        if(!cull)    // If the object was not culled
//    //        //        {
//    //        // Set the treesToDrawIndex in the constant buffer. We are rearanging the tree instance positions, so that the trees
//    //        // that will be drawn have their positions first. This way, when the GPU loops through the instances, it will first
//    //        // get all the tree positions that we want to draw. We are not going to have the GPU draw all 4000 trees, only the couple
//    //        // that are in the view frustum, so we want those tree positions to be the first ones in the instance buffer array
//    //        //            tempTreeInstDat[numTreesToDraw].pos = treeInstanceData[i].pos;

//    //        // Add one to the number of trees to draw
//    //        //            numTreesToDraw++;
//    //        //        }
//    //        return cull;

//    // Update our instance buffer with our new (newly ordered) array of tree instance data (positions)
//    //    d3d11DevCon->UpdateSubresource( treeInstanceBuff, 0, NULL, &tempTreeInstDat[0], 0, 0 );
//    //}
//}
