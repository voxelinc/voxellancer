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
        extendBulletBuffers();
    }

    bullet->setPrototype(this);

    int slot = m_freeBulletSlots.top();
    m_freeBulletSlots.pop();

    bullet->setBufferSlot(slot);
    m_cpuBulletBuffer[slot].active = true;

    updateGPUBuffer(slot);
}

void InstancedBulletPrototype::remove(InstancedBullet* bullet) {
    if (!m_initialized) {
        initialize();
    }

    int slot = bullet->bufferSlot();

    m_freeBulletSlots.push(slot);

    m_cpuBulletBuffer[slot].active = false;

    updateGPUBulletBuffer(slot);

    bullet->setPrototype(nullptr);
}

void InstancedBulletPrototype::draw(const Camera& camera, glow::Program* program) {
    assert(program->isUsed());

    if (!m_initialized) {
        initialize();
    }

    program->setUniform("scale", m_worldObjectBullet->transform().scale());

    glVertexAttribDivisor(program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(program->getAttributeLocation("v_normal"), 0);

    glVertexAttribDivisor(program->getAttributeLocation("v_cell"), 1);
    glVertexAttribDivisor(program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(program->getAttributeLocation("v_emissiveness"), 1);

    int voxelCount = m_worldObjectBullet->voxelMap().size();

    glVertexAttribDivisor(program->getAttributeLocation("v_active"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_creationPosition"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_creationEulers"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_directionalSpeed"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_angularSpeed"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_creationTime"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_deathTime"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_color"), voxelCount);
    glVertexAttribDivisor(program->getAttributeLocation("v_emissiveness"), voxelCount);

    std::cout << "InstancedBulletPrototype drawing " << m_cpuBulletBuffer.size() << " bullets" << std::endl;

    m_vao->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, voxelCount * m_cpuBulletBuffer.size());
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

    std::vector<InstancedBulletVoxelData> bufferData;
    for (auto& pair : m_worldObjectBullet->voxelMap()) {
        InstancedBulletVoxelData data(pair.second);
        bufferData.push_back(data);
    }

    m_gridBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_gridBuffer->setData(bufferData);
}

void InstancedBulletPrototype::initializeBullets() {
    m_gpuBulletBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
}

void InstancedBulletPrototype::extendBulletBuffers() {
    int newBulletBufferSize = m_bulletBufferSize * 2;

    m_cpuBulletBuffer.resize(newBulletBufferSize);
    for (int i = m_bulletBufferSize; i < newBulletBufferSize; ++i) {
        m_freeBulletSlots.push(i);
    }

    m_gpuBulletBuffer.setData(m_cpuBulletBuffer);
}

void InstancedBulletPrototype::updateGPUBulletBuffer(int slot) {
    InstancedBullet::Data* data = &m_cpuBulletBuffer[slot];
    m_gpuBulletBuffer->setSubData(slot * sizeof(*data), sizeof(*data), data);
}

void InstancedBulletPrototype::beforeContextDestroy() {
    m_initialized = false;
    m_bulletBufferSize = 0;
}

void InstancedBulletPrototype::afterContextRebuild() {

}

