#pragma once

#include <string>

#include <glow/ref_ptr.h>
#include <glow/Array.h>

#include <glm/glm.hpp>


namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
};


class Mesh {
public:
    Mesh();
    void bindTo(glow::Program* program,
                       glow::VertexArrayObject* vao,
                       int bindingIndex);

protected:
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void setupVertexAttribute(glow::Program* program, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset);
    void initBuffer();
};
