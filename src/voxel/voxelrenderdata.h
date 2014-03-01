#pragma once

#include <unordered_map>
#include <string>

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

class IVoxelRenderData {
public:
    virtual void invalidate() = 0;
    virtual int voxelCount() = 0;
    virtual bool isInstanced() = 0;

    virtual glow::VertexArrayObject* vertexArrayObject() = 0;
};

class VoxelRenderData;

class InstancedVoxelRenderData : public IVoxelRenderData {
public:
    InstancedVoxelRenderData(const IVoxelRenderData& prototype);

    virtual void invalidate() override; // throws assertion or just do nothing
    virtual int voxelCount() override;
    virtual bool isInstanced() override;

    virtual glow::VertexArrayObject* vertexArrayObject() override;

protected:
    const VoxelRenderData& m_prototype;

};

class VoxelRenderData : public IVoxelRenderData, ContextDependant {
public:
    VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel);

    virtual void invalidate() override;
    virtual int voxelCount() override;
    virtual bool isInstanced() override;

    virtual glow::VertexArrayObject* vertexArrayObject() override;

protected:
    std::unordered_map<glm::ivec3, Voxel*> &m_voxel;
    bool m_isDirty;
    int m_bufferSize;

    glow::ref_ptr<glow::Buffer> m_voxelDataBuffer;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    void updateBuffer();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

