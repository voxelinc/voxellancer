#include "objecthudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "objecthudget.h"


class ObjectHudgetCorner {
public:
    ObjectHudgetCorner(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset):
        m_objectHudgetVoxels(objectHudgetVoxels),
        m_baseOffset(baseOffset),
        m_voxelCluster(0.05f)
    {
        m_baseOrientation = glm::quat(glm::vec3(-m_baseOffset.y, -m_baseOffset.x, 0));

        int color = 0x66AAFF;

        int edgeLength = 3;
        m_voxelCluster.addVoxel(new Voxel(glm::ivec3(edgeLength, edgeLength, 0), color));
        m_voxelCluster.transform().setCenter(glm::vec3(edgeLength, edgeLength, 0));

        for(int i = 1; i < edgeLength; i++) {
            m_voxelCluster.addVoxel(new Voxel(glm::ivec3(-baseOffset.x * i + edgeLength, edgeLength, 0), color));
            m_voxelCluster.addVoxel(new Voxel(glm::ivec3(edgeLength, baseOffset.y * i + edgeLength, 0), color));
        }
    }

    void draw() {
        ObjectHudget* objectHudget = m_objectHudgetVoxels->hudget();
        glm::vec3 euler = glm::vec3(-m_baseOffset.y, -m_baseOffset.x, 0) * (m_objectHudgetVoxels->openingAngle());
        glm::quat orientation = objectHudget->orientation() * glm::quat(euler);

        m_voxelCluster.transform().setPosition(objectHudget->position() + orientation * glm::vec3(0, 0, -objectHudget->hud()->sphere().radius()));
        m_voxelCluster.transform().setOrientation(orientation);

        VoxelRenderer::instance()->draw(&m_voxelCluster);
    }


protected:
    ObjectHudgetVoxels* m_objectHudgetVoxels;
    glm::ivec3 m_baseOffset;
    glm::quat m_baseOrientation;
    VoxelCluster m_voxelCluster;
};


ObjectHudgetVoxels::ObjectHudgetVoxels(ObjectHudget* hudget):
    m_hudget(hudget),
    m_openingAngle(0.0f)
{
    setupCorners();
}

ObjectHudgetVoxels::~ObjectHudgetVoxels() {
    delete m_lu;
    delete m_lb;
    delete m_ru;
    delete m_rb;
}

ObjectHudget* ObjectHudgetVoxels::hudget() {
    return m_hudget;
}

float ObjectHudgetVoxels::openingAngle() const {
    return m_openingAngle;
}

void ObjectHudgetVoxels::setOpeningAngle(float openingAngle) {
    m_openingAngle = openingAngle;
}

void ObjectHudgetVoxels::draw() {
    m_lu->draw();
    m_lb->draw();
    m_ru->draw();
    m_rb->draw();
}

void ObjectHudgetVoxels::setupCorners() {
    m_lu = new ObjectHudgetCorner(this, glm::ivec3(-1, 1, 0));
    m_lb = new ObjectHudgetCorner(this, glm::ivec3(-1, -1, 0));
    m_ru = new ObjectHudgetCorner(this, glm::ivec3(1, 1, 0));
    m_rb = new ObjectHudgetCorner(this, glm::ivec3(1, -1, 0));
}

