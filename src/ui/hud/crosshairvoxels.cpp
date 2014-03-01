#include "crosshairvoxels.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "utils/randfloat.h"

#include "voxel/renderer/voxelrenderer.h"

#include "crosshair.h"
#include "hud.h"
#include "voxel/voxel.h"


class CrossHairElement: public VoxelCluster {
public:
    CrossHairElement():
        VoxelCluster(0.08f),
        zOrientation(0.0f)
    {
    };

    glm::quat relativeOrientation;
    float zOrientation;
};

static CrossHairElement* newStick() {
    int color = 0x33FF00;

    CrossHairElement* stick = new CrossHairElement();

    for(int v = 0; v < 6; v++) {
        stick->addVoxel(new Voxel(glm::ivec3(v, 0, 0), color));
    }

    return stick;
}

static CrossHairElement* newDot() {
    CrossHairElement* dot = new CrossHairElement();
    dot->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0x33FF00));
    return dot;
}

CrossHairVoxels::CrossHairVoxels(CrossHair* crossHair):
    m_crossHair(crossHair)
{
    float baseX = 0.06f;
    float baseY = 0.03f;

    CrossHairElement *lu = newStick();
    lu->relativeOrientation = glm::quat(glm::vec3(baseY, baseX, 0.0f));
    lu->zOrientation = glm::radians(150.0f);

    CrossHairElement *lb = newStick();
    lb->relativeOrientation = glm::quat(glm::vec3(-baseY, baseX, 0.0f));
    lb->zOrientation = glm::radians(210.0f);

    CrossHairElement *ru = newStick();
    ru->relativeOrientation = glm::quat(glm::vec3(baseY, -baseX, 0.0f));
    ru->zOrientation = glm::radians(30.0f);

    CrossHairElement *rb = newStick();
    rb->relativeOrientation = glm::quat(glm::vec3(-baseY, -baseX, 0.0f));
    rb->zOrientation = glm::radians(330.0f);

    CrossHairElement *dot = newDot();
    dot->relativeOrientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
    dot->zOrientation = 0.0f;

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

}

void CrossHairVoxels::draw() {
    for(CrossHairElement* element : m_crossHairElements) {
        element->transform().setPosition(m_crossHair->worldPosition() + (m_crossHair->worldOrientation() * element->relativeOrientation * glm::vec3(0, 0, -m_crossHair->hud()->sphere().radius())));
        element->transform().setOrientation(m_crossHair->worldOrientation() * element->relativeOrientation * glm::quat(glm::vec3(0, 0, element->zOrientation)));

        VoxelRenderer::instance()->draw(*element);
    }
}

