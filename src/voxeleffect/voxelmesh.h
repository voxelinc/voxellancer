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
    void bindTo(GLint v_vectexLocation,
                GLint v_normalLocation,
                int vertexBindingIndex,
                int normalBindingIndex,
                glow::VertexArrayObject* vao
                );

protected:
    bool m_initialized;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void setupVertexAttribute(GLint location, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset);
    
    void initialize();

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

