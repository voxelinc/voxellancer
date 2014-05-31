#include "voxelrenderdata.h"

#include <vector>

#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Buffer.h>
#include <glow/Program.h>

#include "utils/colorhelper.h"

#include "voxelcluster.h"
#include "voxeleffect/voxelmesh.h"
#include "voxelrenderer.h"
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
    m_bufferSize(0),
    m_transparentCount(0)
{

}

void VoxelRenderData::setupVertexAttributes() {
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_voxelDataBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    VoxelRenderer::voxelMesh().bindTo(VoxelRenderer::program(), m_vertexArrayObject, 0);
    setupVertexAttribute(offsetof(VoxelData, position), "v_position", 3, GL_FLOAT, GL_FALSE, 2);
    setupVertexAttribute(offsetof(VoxelData, color), "v_color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, 3);
    setupVertexAttribute(offsetof(VoxelData, emissiveness), "v_emissiveness", 1, GL_FLOAT, GL_FALSE, 4);
}

void VoxelRenderData::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = VoxelRenderer::program()->getAttributeLocation(name);

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

    m_transparentCount = 0;
    int opaqueCursor = 0; // counts from front, opaque voxels
    int transparentCursor = m_bufferSize - 1; // counts from back, transparent voxels
    for (auto& pair : m_voxel) {
        Voxel *voxel = pair.second;
        assert(voxel != nullptr);
        uint32_t color = voxel->visuals().color();
        VoxelData data = VoxelData{ glm::vec3(voxel->gridCell()), ColorHelper::flipColorForGPU(color), voxel->visuals().emissiveness() };
        if ((color & 0x000000FF) == 0xFF) {
            voxelData[opaqueCursor++] = data;
        } else {
            voxelData[transparentCursor--] = data;
            m_transparentCount++;
        }
    }

    m_voxelDataBuffer->unmap();

    m_isDirty = false;
}

int VoxelRenderData::opaqueVoxelCount() {
    if (m_isDirty) {
        updateBuffer();
    }
    return m_voxel.size() - m_transparentCount;
}

int VoxelRenderData::transparentVoxelCount() {
    if (m_isDirty) {
        updateBuffer();
    }
    return m_transparentCount;
}

int VoxelRenderData::transparentVoxelBase() {
    if (m_isDirty) {
        updateBuffer();
    }
    return m_bufferSize - m_transparentCount;
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

