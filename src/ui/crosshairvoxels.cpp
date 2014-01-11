#include "crosshairvoxels.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "voxel/voxelrenderer.h"

#include "crosshair.h"


class CrossHairElement: public VoxelCluster {
public:
    CrossHairElement(): VoxelCluster(0.05f) {};

    glm::vec3 relativePosition;
    glm::quat relativeOrientation;
};

static CrossHairElement* newStick() {
    CrossHairElement* stick = new CrossHairElement();
    stick->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFAA00));
    stick->addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFAA00));
    stick->addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFAA00));
    stick->addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFAA00));
    stick->addVoxel(new Voxel(glm::ivec3(4, 0, 0), 0xFFAA00));
    stick->addVoxel(new Voxel(glm::ivec3(5, 0, 0), 0xFFAA00));
    return stick;
}

static CrossHairElement* newDot() {
    CrossHairElement* dot = new CrossHairElement();
    dot->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFAAAAFF));
    return dot;
}

CrossHairVoxels::CrossHairVoxels(CrossHair* crossHair):
    m_crossHair(crossHair)
{
    float baseX = 0.5f;
    float baseY = 0.2f;

    CrossHairElement *lu = newStick();
    lu->relativeOrientation = glm::angleAxis(150.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    lu->relativePosition = glm::vec3(-baseX, baseY, 0.0f);
    CrossHairElement *lb = newStick();
    lb->relativeOrientation = glm::angleAxis(210.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    lb->relativePosition = glm::vec3(-baseX, -baseY, 0.0f);
    CrossHairElement *ru = newStick();
    ru->relativeOrientation = glm::angleAxis(330.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    ru->relativePosition = glm::vec3(baseX, -baseY, 0.0f);
    CrossHairElement *rb = newStick();
    rb->relativeOrientation = glm::angleAxis(30.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    rb->relativePosition = glm::vec3(baseX, baseY, 0.0f);

    CrossHairElement *dot = newDot();
    dot->relativePosition = glm::vec3(0.0f, 0.0f, -0.0f);

    m_crossHairElements.push_back(lu);
    m_crossHairElements.push_back(lb);
    m_crossHairElements.push_back(ru);
    m_crossHairElements.push_back(rb);
    m_crossHairElements.push_back(dot);
}

CrossHairVoxels::~CrossHairVoxels() {
    for(CrossHairElement* crossHairElement : m_crossHairElements) {
        delete crossHairElement;
    }
}

void CrossHairVoxels::update(float deltaSec) {
    for(CrossHairElement* crossHairElement : m_crossHairElements) {
        WorldTransform transform(crossHairElement->transform());
        transform.setPosition(m_crossHair->position() + m_crossHair->orientation() * crossHairElement->relativePosition);
        transform.setOrientation(m_crossHair->orientation() * crossHairElement->relativeOrientation);

        crossHairElement->setTransform(transform);
    }
}

void CrossHairVoxels::draw() {
    for(CrossHairElement* crossHairElement : m_crossHairElements) {
        VoxelRenderer::instance()->draw(crossHairElement);
    }
}
