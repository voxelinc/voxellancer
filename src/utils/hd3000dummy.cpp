#include <glm/glm.hpp>

#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>

#include "hd3000dummy.h"


HD3000Dummy::HD3000Dummy():
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_usedummy("general.hd3000workaround", false)
{
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(glow::Array<glm::vec3>{glm::vec3(0, 0, 0)});
}

HD3000Dummy::~HD3000Dummy()
{

}

void HD3000Dummy::draw()
{
    if (m_usedummy)
        m_vertexArrayObject->drawArrays(GL_TRIANGLE_STRIP, 0, 1);
}
