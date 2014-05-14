#pragma once

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class VertexArrayObject;
    class Buffer;
}

class Camera;

class ScreenQuad : public ContextDependant {
public:
    static const int VERTEX_ATTRIBUTE_LOCATION = 0;

    ScreenQuad();

    void draw();


protected:
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void initialize();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

