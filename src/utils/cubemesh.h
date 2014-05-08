#pragma once

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

/**
 * Provides the geometry of a unit-cube
 * Note that the lifetime of this class has to be >= the lifetime of the program/vao
 * it is bound to, otherwise their behaviour is undefined
 */
class CubeMesh : public ContextDependant {
public:
    CubeMesh();

    int numLineVertices() const;
    void bindLinesTo(glow::Program& program, glow::VertexArrayObject& vao, int bindingIndex);


protected:
    bool m_initialized;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void initialize();
    void beforeContextDestroy();
    void afterContextRebuild();
};

