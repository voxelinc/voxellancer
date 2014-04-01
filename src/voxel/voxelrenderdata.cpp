#include "voxelrenderdata.h"

#include <vector>

#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Buffer.h>
#include <glow/Program.h>

#include "utils/tostring.h"

#include "voxelcluster.h"
#include "voxeleffect/voxelmesh.h"
#include "renderer/voxelrenderer.h"
#include "voxel.h"


namespace {
    struct VoxelData {
        glm::vec3 position;
        uint32_t color;
        float emissiveness;
    };
}

VoxelRenderData::VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel) :
    m_voxel(voxel),
    m_isDirty(true),
    m_bufferSize(0)
{

}

void VoxelRenderData::setupVertexAttributes() {
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_voxelDataBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    int vertexLocation = VoxelRenderer::instance()->getAttributeLocation("v_vertex");
    int normalLocation = VoxelRenderer::instance()->getAttributeLocation("v_normal");
    VoxelRenderer::voxelMesh().bindTo(vertexLocation, normalLocation, 0, 1, m_vertexArrayObject);

    setupVertexAttribute(offsetof(VoxelData, position), "v_position", 3, GL_FLOAT, GL_FALSE, 2);
    setupVertexAttribute(offsetof(VoxelData, color), "v_color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, 3);
    setupVertexAttribute(offsetof(VoxelData, emissiveness), "v_emissiveness", 1, GL_FLOAT, GL_FALSE, 4);
}

int VoxelRenderData::bindings() {
    return 5; // bindings 0-4 are used
}

void VoxelRenderData::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = VoxelRenderer::instance()->getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(m_voxelDataBuffer, 0, sizeof(VoxelData));
    binding->setFormat(numPerVertex, type, normalised, offset);

    m_vertexArrayObject->enable(location);
}

void VoxelRenderData::updateBuffer() {
    if (!m_vertexArrayObject) {
        setupVertexAttributes();
    }

    if (m_voxel.empty()) {
        return;
    }

    if (m_bufferSize < m_voxel.size() || m_bufferSize > m_voxel.size() * 2) {
        m_voxelDataBuffer->setData(m_voxel.size() * sizeof(VoxelData), nullptr, GL_DYNAMIC_DRAW);
        m_bufferSize = m_voxel.size();
    }

    VoxelData* voxelData = static_cast<VoxelData*>(m_voxelDataBuffer->mapRange(0, m_voxel.size() * sizeof(VoxelData), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
    assert(voxelData != nullptr);

    int i = 0;
    for (auto& pair : m_voxel) {
        Voxel *voxel = pair.second;
        assert(voxel != nullptr);
        voxelData[i++] = VoxelData{ glm::vec3(voxel->gridCell()), voxel->visuals().color(), voxel->visuals().emissiveness() };
    }

    m_voxelDataBuffer->unmap();

    m_isDirty = false;
}

int VoxelRenderData::voxelCount() {
    return m_voxel.size();
}

void VoxelRenderData::invalidate() {
    m_isDirty = true;
}

glow::VertexArrayObject* VoxelRenderData::vertexArrayObject() {
    if (m_isDirty) {
        updateBuffer();
    }
    return m_vertexArrayObject;
}

void VoxelRenderData::beforeContextDestroy() {
    m_vertexArrayObject = nullptr;
    m_voxelDataBuffer = nullptr;
    // trigger a setup on next update
    m_isDirty = true;
    m_bufferSize = 0;
}

void VoxelRenderData::afterContextRebuild() {
    // lazy init
}

bool VoxelRenderData::isInstanced() {
    return false;
}

InstancedVoxelRenderData::InstancedVoxelRenderData(IVoxelRenderData& prototype):
    m_prototype(prototype)
{
    assert(!m_prototype.isInstanced());
}

void InstancedVoxelRenderData::invalidate() {
    m_prototype.invalidate();
}

int InstancedVoxelRenderData::voxelCount() {
    return m_prototype.voxelCount();
}

bool InstancedVoxelRenderData::isInstanced() {
    return true;
}

glow::VertexArrayObject* InstancedVoxelRenderData::vertexArrayObject() {
    return m_prototype.vertexArrayObject();
}

int InstancedVoxelRenderData::bindings() {
    return m_prototype.bindings();
}
