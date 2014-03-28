#pragma once

#include "etc/contextdependant.h"


namespace glow {
    class Program;
    class VertexArrayBinding;
}

class CubeMesh : public ContextDependant {
public:
    CubeMesh();

    void bindLinestripTo(glow::Program& program, glow::VertexArrayBinding* vertexBinding);


protected:
    bool m_initialized;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void initialize();
};
