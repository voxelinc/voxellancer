#include "instancedbulletprototype.h"

#include <cassert>
#include <iostream>

#include <glow/Buffer.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>

#include "resource/worldelementbuilder.h"

#include "voxeleffect/voxelmesh.h"

#include "equipment/weapons/worldobjectbullet.h"

#include "bulletenginerenderer.h"
#include "instancedbullet.h"
#include "instancedbulletvoxeldata.h"


InstancedBulletPrototype::InstancedBulletPrototype(BulletEngineRenderer& renderer, const std::string& name):
    m_renderer(renderer),
    m_initialized(false),
    m_name(name),
    m_bulletBufferSize(0)
{
}

void InstancedBulletPrototype::add(InstancedBullet* bullet) {
    if (!m_initialized) {
        initialize();
    }

    if (m_freeBulletSlots.empty()) {
        allocateBulletSlots();
    }

    bullet->setBufferSlot(m_freeBulletSlots.top());
    m_freeBulletSlots.pop();

    m_bulletBuffer->setSubData(bullet->bufferSlot() * sizeof(*bullet->data()), sizeof(*bullet->data()), bullet->data());
}

void InstancedBulletPrototype::remove(InstancedBullet* bullet) {
    if (!m_initialized) {
        initialize();
    }
}

void InstancedBulletPrototype::draw(const Camera& camera, glow::Program* program) {
    assert(program->isUsed());

    if (!m_initialized) {
        initialize();
    }

    program->setUniform("scale", m_worldObjectBullet->transform().scale());

    glVertexAttribDivisor(program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(program->getAttributeLocation("v_normal"), 0);

    glVertexAttribDivisor(program->getAttributeLocation("v_active"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_cell"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_color"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_emissiveness"), m_voxelCount);

    glVertexAttribDivisor(program->getAttributeLocation("v_creationPosition"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_creationEulers"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_directionalSpeed"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_angularSpeed"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_creationTime"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_deathTime"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_color"), m_voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_emissiveness"), m_voxelCount);

    m_vao->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_bulletBufferSize);
}

void InstancedBulletPrototype::initialize() {
    m_vao = new glow::VertexArrayObject();
    m_renderer.bindVoxelMeshTo(m_vao);

    initializeGrid();
    initializeBullets();

    m_initialized = true;
}

void InstancedBulletPrototype::initializeGrid() {
    m_worldObjectBullet.reset(WorldElementBuilder(m_name).buildWorldObjectBullet());

    m_voxelCount = m_worldObjectBullet->voxelMap().size();

    std::vector<InstancedBulletVoxelData> bufferData;
    for (auto pair : m_worldObjectBullet->voxelMap()) {
        InstancedBulletVoxelData data(pair.second);
        bufferData.push_back(data);
    }

    m_gridBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_gridBuffer->setData(bufferData);
}

void InstancedBulletPrototype::initializeBullets() {
    m_bulletBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
}

void InstancedBulletPrototype::allocateBulletSlots() {

}

void InstancedBulletPrototype::beforeContextDestroy() {
    m_initialized = false;
    m_bulletBufferSize = 0;
}

void InstancedBulletPrototype::afterContextRebuild() {

}

