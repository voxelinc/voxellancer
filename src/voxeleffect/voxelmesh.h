#pragma once

#include <string>

#include <GL/glew.h>

#include <glow/ref_ptr.h>

#include <glm/glm.hpp>

#include "etc/contextdependant.h"


namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
};


class VoxelMesh : public ContextDependant {
public:
    VoxelMesh();

    void bindTo(glow::Program* program,
                glow::VertexArrayObject* vao,
                int bindingIndex);

    void bindTo(glow::VertexArrayObject* vao,
                int vertexBindingIndex, int vertexLocation,
                int normalBindingIndex, int normalLocation);

protected:
    bool m_initialized;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;


    void initialize();

    void setupVertexAttribute(GLint location, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

