#pragma once

#include <unordered_map>
#include <string>
#include <stdint.h>

#include <GL/glew.h>

#include <glow/ref_ptr.h>

#include "utils/vec3hash.h"
#include "etc/contextdependant.h"

namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
    class Texture;
};
class Voxel;

class VoxelRenderData : public ContextDependant {
public:
    VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel);

    void invalidate();
    int voxelCount();

    glow::VertexArrayObject* vertexArrayObject();

protected:
    std::unordered_map<glm::ivec3, Voxel*> &m_voxel;
    bool m_isDirty;
    int m_bufferSize;

    glow::ref_ptr<glow::Buffer> m_voxelDataBuffer;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    uint32_t colorFor(Voxel* voxel, const glm::ivec3& offset);
    void updateBuffer();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

