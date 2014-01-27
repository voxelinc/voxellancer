#include "quad.h"

#include <glow/Buffer.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>


static GLfloat vertices[] = {
    -1.0f, 1.0f,
    -1.0f, -1.0f,
    1.0f, 1.0f,
    1.0f, -1.0f
};

Quad::Quad():
    m_vertexArrayObject(),
    m_vertexBuffer()
{
}

void Quad::draw() {
    if (!m_vertexArrayObject) {
        initialize();
    }

    m_vertexArrayObject->drawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Quad::initialize() {
    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(sizeof(vertices), vertices);

    m_vertexArrayObject = new glow::VertexArrayObject();
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(0);
    binding->setAttribute(VERTEX_ATTRIBUTE_LOCATION);
    binding->setBuffer(m_vertexBuffer, 0, sizeof(GLfloat)* 2);
    binding->setFormat(2, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject->enable(VERTEX_ATTRIBUTE_LOCATION);
}

