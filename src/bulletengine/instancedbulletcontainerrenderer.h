#pragma once

#include <memory>
#include <vector>

#include <glow/Buffer.h>
#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"

#include "voxel/voxeldata.h"


namespace glow {
    class Buffer;
    class VertexArrayObject;
}

class InstancedBulletContainer;
class VoxelMesh;

/**
 * Renders all InstancedBullets belonging to a InstancedBulletContainer
 */
class InstancedBulletContainerRenderer : public ContextDependant {
public:
    InstancedBulletContainerRenderer(InstancedBulletContainer& container);
    ~InstancedBulletContainerRenderer();

    void invalidateSlot(int slot);

    void draw();


protected:
    void initialize();

    void setupVertexAttribute(glow::Buffer * buffer, int stride, int bindingNum, const std::string& name, GLint offset, int numPerVertex, GLenum type, GLboolean normalise = GL_FALSE);

    void updateSlots(int begin, int end);
    void allocateSlots(int slotCount);

    void setVertexAttribDivisors();
    void setVertexAttribDivisor(const std::string& name, int divisor);

    void beforeContextDestroy();
    void afterContextRebuild();


protected:
    InstancedBulletContainer& m_container;

    bool m_initialized;

    int m_slotCount;

    bool m_slotsInvalid;
    int m_invalidSlotsBegin;
    int m_invalidSlotsEnd;

    std::unique_ptr<VoxelMesh> m_voxelMesh;

    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    glow::ref_ptr<glow::Buffer> m_gridBuffer;
    glow::ref_ptr<glow::Buffer> m_bulletBuffer;
};

