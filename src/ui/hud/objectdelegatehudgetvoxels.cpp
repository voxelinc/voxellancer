#include "objectdelegatehudgetvoxels.h"

#include "voxel/voxelrenderer.h"

#include "objectdelegatehudget.h"


ObjectDelegateHudgetVoxels::ObjectDelegateHudgetVoxels(ObjectDelegateHudget* hudget):
    m_hudget(hudget)
{
    setupCorners();
}

ObjectDelegateHudgetVoxels::~ObjectDelegateHudgetVoxels() {
    delete m_lu;
    delete m_lb;
    delete m_ru;
    delete m_rb;
}

void ObjectDelegateHudgetVoxels::setEdgeLength(float edgeLength) {
    m_edgeLength = edgeLength;
}

void ObjectDelegateHudgetVoxels::draw() {
    m_lu->transform().setPosition(m_hudget->position() + m_hudget->orientation() * (glm::vec3(-0.7, 0.7, 0) * m_edgeLength / 2.0f));
   // m_lu->transform().setOrientation(m_hudget->orientation());
    VoxelRenderer::instance()->draw(m_lu);

    m_lb->transform().setPosition(m_hudget->position() + m_hudget->orientation() * (glm::vec3(-0.7, -0.7, 0) * m_edgeLength / 2.0f));
  //  m_lb->transform().setOrientation(m_hudget->orientation());
    VoxelRenderer::instance()->draw(m_lb);

    m_ru->transform().setPosition(m_hudget->position() + m_hudget->orientation() * (glm::vec3(0.7, 0.7, 0) * m_edgeLength / 2.0f));
  //  m_ru->transform().setOrientation(m_hudget->orientation());
    VoxelRenderer::instance()->draw(m_ru);

    m_rb->transform().setPosition(m_hudget->position() + m_hudget->orientation() * (glm::vec3(0.7, -0.7, 0) * m_edgeLength / 2.0f));
 //   m_rb->transform().setOrientation(m_hudget->orientation());
    VoxelRenderer::instance()->draw(m_rb);
}

void ObjectDelegateHudgetVoxels::setupCorners() {
    float size = 0.1;

    m_lu = new VoxelCluster(size);
    m_lu->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0x999999));
    m_lu->addVoxel(new Voxel(glm::ivec3(0, 1, 0), 0x999999));
    m_lu->addVoxel(new Voxel(glm::ivec3(1, 1, 0), 0x999999));

    m_lb = new VoxelCluster(size);
    m_lb->addVoxel(new Voxel(glm::ivec3(0, 1, 0), 0x999999));
    m_lb->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0x999999));
    m_lb->addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0x999999));

    m_ru = new VoxelCluster(size);
    m_ru->addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0x999999));
    m_ru->addVoxel(new Voxel(glm::ivec3(1, 1, 0), 0x999999));
    m_ru->addVoxel(new Voxel(glm::ivec3(0, 1, 0), 0x999999));

    m_rb = new VoxelCluster(size);
    m_rb->addVoxel(new Voxel(glm::ivec3(1, 1, 0), 0x999999));
    m_rb->addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0x999999));
    m_rb->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0x999999));
}
