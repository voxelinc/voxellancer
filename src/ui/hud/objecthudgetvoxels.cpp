#include "objecthudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>

#include "utils/geometryhelper.h"
#include "voxel/voxelrenderer.h"
#include "hud.h"
#include "objecthudget.h"
#include "geometry/transform.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"


namespace {
    class ObjectHudgetCorner: public VoxelCluster {
    public:
        ObjectHudgetCorner(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset, bool targetHightlight):
            VoxelCluster(targetHightlight ? 0.04f : 0.02f),
            m_objectHudgetVoxels(objectHudgetVoxels),
            m_baseOffset(baseOffset)
        {
            int color = targetHightlight ? 0x99CCFF : 0x66AAFF;

            int edgeLength = 3;
            addVoxel(new Voxel(glm::ivec3(edgeLength, edgeLength, 0), color));
            transform().setCenter(glm::vec3(edgeLength, edgeLength, 0));

            for(int i = 1; i < edgeLength; i++) {
                addVoxel(new Voxel(glm::ivec3(-baseOffset.x * i + edgeLength, edgeLength, 0), color));
                addVoxel(new Voxel(glm::ivec3(edgeLength, baseOffset.y * i + edgeLength, 0), color));
            }
        }

        void draw() {
            ObjectHudget* objectHudget = m_objectHudgetVoxels->hudget();

            glm::vec3 euler = glm::vec3(-m_baseOffset.y, -m_baseOffset.x, 0) * (m_objectHudgetVoxels->openingAngle());
            glm::vec3 direction = GeometryHelper::quatFromViewDirection(objectHudget->localDirection()) * glm::quat(euler) * glm::vec3(0, 0, -1);

            transform().setPosition(objectHudget->worldPosition(direction));
            transform().setOrientation(objectHudget->worldOrientation(direction));

            VoxelRenderer::instance()->draw(*this);
        }


    protected:
        ObjectHudgetVoxels* m_objectHudgetVoxels;
        glm::ivec3 m_baseOffset;
    };
}




ObjectHudgetVoxels::ObjectHudgetVoxels(ObjectHudget* hudget):
    m_hudget(hudget),
    m_openingAngle(0.0f),
    m_targetHightlight(false)
{
    setupCorners();
}

ObjectHudgetVoxels::~ObjectHudgetVoxels() {
    delete m_lu[0];
    delete m_lb[0];
    delete m_ru[0];
    delete m_rb[0];
    delete m_lu[1];
    delete m_lb[1];
    delete m_ru[1];
    delete m_rb[1];
}

ObjectHudget* ObjectHudgetVoxels::hudget() {
    return m_hudget;
}

void ObjectHudgetVoxels::setTargetHightlight(bool targetHightlight) {
    m_targetHightlight = targetHightlight;
}

float ObjectHudgetVoxels::openingAngle() const {
    return m_openingAngle;
}

void ObjectHudgetVoxels::setOpeningAngle(float openingAngle) {
    m_openingAngle = openingAngle;
}

void ObjectHudgetVoxels::draw() {
    int index = m_targetHightlight ? 1 : 0;

    m_lu[index]->draw();
    m_lb[index]->draw();
    m_ru[index]->draw();
    m_rb[index]->draw();
}

void ObjectHudgetVoxels::setupCorners() {
    m_lu[0] = new ObjectHudgetCorner(this, glm::ivec3(-1, 1, 0), false);
    m_lb[0] = new ObjectHudgetCorner(this, glm::ivec3(-1, -1, 0), false);
    m_ru[0] = new ObjectHudgetCorner(this, glm::ivec3(1, 1, 0), false);
    m_rb[0] = new ObjectHudgetCorner(this, glm::ivec3(1, -1, 0), false);

    m_lu[1] = new ObjectHudgetCorner(this, glm::ivec3(-1, 1, 0), true);
    m_lb[1] = new ObjectHudgetCorner(this, glm::ivec3(-1, -1, 0), true);
    m_ru[1] = new ObjectHudgetCorner(this, glm::ivec3(1, 1, 0), true);
    m_rb[1] = new ObjectHudgetCorner(this, glm::ivec3(1, -1, 0), true);
}

