#include "instancedbulletcontainerrenderer.h"

#include <iostream>

#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>

#include "equipment/weapons/worldobjectbullet.h"

#include "utils/math.h"
#include "utils/tostring.h"

#include "voxel/voxeldata.h"

#include "voxeleffect/voxelmesh.h"

#include "bulletengine.h"
#include "bulletenginerenderer.h"
#include "instancedbulletcontainer.h"


InstancedBulletContainerRenderer::InstancedBulletContainerRenderer(InstancedBulletContainer& container):
    m_container(container),
    m_slotsInvalid(false),
    m_invalidSlotsBegin(0),
    m_invalidSlotsEnd(0),
    m_slotCount(0),
    m_initialized(false)
{

}

InstancedBulletContainerRenderer::~InstancedBulletContainerRenderer() = default;

void InstancedBulletContainerRenderer::invalidateSlot(int slot) {
    std::cout << "Invalidating slot " << slot << std::endl;
    int oldInvalidBegin = m_invalidSlotsBegin;
    int oldInvalidEnd = m_invalidSlotsEnd;

    if (m_slotsInvalid) {
        if(slot < m_invalidSlotsBegin) {
            m_invalidSlotsBegin = slot;
        } else if (slot > m_invalidSlotsEnd) {
            m_invalidSlotsEnd = slot;
        }
    } else {
        m_slotsInvalid = true;
        m_invalidSlotsBegin = slot;
        m_invalidSlotsEnd = slot;
    }

    int oldInvalidCount = oldInvalidEnd - oldInvalidBegin;
    int newInvalidCount = m_invalidSlotsEnd - m_invalidSlotsBegin;

    if (m_initialized && newInvalidCount - oldInvalidCount > 64) {
        updateSlots(oldInvalidBegin, oldInvalidEnd);

        m_invalidSlotsBegin = slot;
        m_invalidSlotsEnd = slot;
        m_slotsInvalid = true;
    }
}

void InstancedBulletContainerRenderer::draw() {
    if (!m_initialized) {
        initialize();
    }

    if (m_slotsInvalid) {
        if (m_invalidSlotsEnd >= m_slotCount) {
            allocateSlots(Math::nextPowerOf2(m_invalidSlotsEnd));
        }

        updateSlots(m_invalidSlotsBegin, m_invalidSlotsEnd);
        m_slotsInvalid = false;
    }

    setVertexAttribDivisors();

  //  std::cout << "Rendering " << m_container.prototype().voxelCount() << " " << m_slotCount << std::endl;
    m_vao->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_container.prototype().voxelCount() * m_slotCount);
}

void InstancedBulletContainerRenderer::initialize() {
    m_vao = new glow::VertexArrayObject();

    m_voxelMesh.reset(new VoxelMesh);
    m_voxelMesh->bindTo(m_vao, 0, m_container.engine().renderer().location("v_vertex"),
                               1, m_container.engine().renderer().location("v_normal"));

    m_gridBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    setupVertexAttribute(m_gridBuffer, sizeof(VoxelData), 2, "v_gridCell", offsetof(VoxelData, gridCell), 3, GL_FLOAT);
   setupVertexAttribute(m_gridBuffer, sizeof(VoxelData), 3, "v_color", offsetof(VoxelData, color), GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE);
  //  setupVertexAttribute(m_gridBuffer, sizeof(VoxelData), 4, "v_emissiveness", offsetof(VoxelData, emissiveness), 1, GL_FLOAT);

    m_bulletBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    /* setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 5, "v_originPosition", offsetof(InstancedBulletData, originPosition), 3, GL_FLOAT);
   setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 6, "v_originEulers", offsetof(InstancedBulletData, originEulers), 3, GL_FLOAT);
    setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 7, "v_directionalSpeed", offsetof(InstancedBulletData, directionalSpeed), 3, GL_FLOAT);
    setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 8, "v_angularSpeed", offsetof(InstancedBulletData, angularSpeed), 3, GL_FLOAT);
    setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 9, "v_originTime", offsetof(InstancedBulletData, originTime), 1, GL_FLOAT);
    setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 10, "v_deathTime", offsetof(InstancedBulletData, deathTime), 1, GL_FLOAT);
    setupVertexAttribute(m_bulletBuffer, sizeof(InstancedBulletData), 11, "v_active", offsetof(InstancedBulletData, active), 1, GL_FLOAT);*/
}

void InstancedBulletContainerRenderer::setupVertexAttribute(glow::Buffer * buffer, int stride, int bindingNum, const std::string& name, GLint offset, int numPerVertex, GLenum type, GLboolean normalise) {
    glow::VertexAttributeBinding* binding = m_vao->binding(bindingNum);
    GLint location = m_container.engine().renderer().location(name);

    binding->setAttribute(location);
    binding->setBuffer(buffer, 0, stride);
    binding->setFormat(numPerVertex, type, normalise, offset);

    m_vao->enable(location);
}

void InstancedBulletContainerRenderer::updateSlots(int begin, int end) {
    std::cout << "Updating " << begin << " -> " << end << std::endl;

    int slotSize = sizeof(InstancedBulletData);
    m_bulletBuffer->setSubData((end - begin + 1) * slotSize, begin * slotSize, &m_container.bulletData()[begin]);
}

void InstancedBulletContainerRenderer::allocateSlots(int slotCount) {
    int voxelCount = m_container.prototype().voxelCount();
    int voxelInstanced = slotCount * voxelCount;

    m_gridBuffer->setData(voxelCount * sizeof(VoxelData));

    std::cout << m_container.gridPrototype().size() << " " << voxelCount << std::endl;

    for (int i = 0; i < slotCount; i++) {
        for (int j = 0; j < voxelCount; j++) {
            std::cout << "----" << std::endl;
            std::cout << "   |" << toString(m_container.gridPrototype()[j].gridCell) << std::endl;
            std::cout << "   |" << (void*)m_container.gridPrototype()[j].color << std::endl;

        }

        m_gridBuffer->setSubData(sizeof(VoxelData) * voxelCount, i * sizeof(VoxelData) * voxelCount, m_container.gridPrototype().data());
    }

    m_bulletBuffer->setData(slotCount * sizeof(InstancedBulletData));

    m_slotsInvalid = true;
    m_invalidSlotsBegin = 0;
    m_invalidSlotsEnd = slotCount - 1;

    m_slotCount = slotCount;
    std::cout << "Allocated " << m_slotCount << " " << slotCount << std::endl;
}

void InstancedBulletContainerRenderer::setVertexAttribDivisors() {
    setVertexAttribDivisor("v_vertex", 0);
    setVertexAttribDivisor("v_normal", 0);

    setVertexAttribDivisor("v_gridCell", 1);
    setVertexAttribDivisor("v_color", 1);
 //   setVertexAttribDivisor("v_emissiveness", 1);

    int voxelCount = m_container.prototype().voxelCount();
   /* setVertexAttribDivisor("v_originPosition", voxelCount);
      setVertexAttribDivisor("v_originEulers", voxelCount);
    setVertexAttribDivisor("v_directionalSpeed", voxelCount);
    setVertexAttribDivisor("v_angularSpeed", voxelCount);
    setVertexAttribDivisor("v_originTime", voxelCount);
    setVertexAttribDivisor("v_deathTime", voxelCount);
    setVertexAttribDivisor("v_active", voxelCount);*/
}

void InstancedBulletContainerRenderer::setVertexAttribDivisor(const std::string& name, int divisor) {
    glVertexAttribDivisor(m_container.engine().renderer().location(name), divisor);
}

void InstancedBulletContainerRenderer::beforeContextDestroy() {
    m_initialized = false;
}

void InstancedBulletContainerRenderer::afterContextRebuild() {

}
