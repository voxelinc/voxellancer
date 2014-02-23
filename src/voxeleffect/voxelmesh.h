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

protected:
    bool m_initialized;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void setupVertexAttribute(glow::Program* program, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset);
    
    void initialize();

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

