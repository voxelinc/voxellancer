#include "cubemesh.h"

#include <glow/Buffer.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>

#include "etc/contextprovider.h"


namespace {
    const glm::vec3 llf(-0.5f, -0.5f, -0.5f);
    const glm::vec3 llb(-0.5f, -0.5f,  0.5f);
    const glm::vec3 ulf(-0.5f,  0.5f, -0.5f);
    const glm::vec3 ulb(-0.5f,  0.5f,  0.5f);
    const glm::vec3 lrf( 0.5f, -0.5f, -0.5f);
    const glm::vec3 lrb( 0.5f, -0.5f,  0.5f);
    const glm::vec3 urf( 0.5f,  0.5f, -0.5f);
    const glm::vec3 urb( 0.5f,  0.5f,  0.5f);
}

CubeMesh::CubeMesh():
    m_initialized(false)
{
}

int CubeMesh::numLineVertices() const {
    return 24;
}

void CubeMesh::bindLinesTo(glow::Program& program, glow::VertexArrayObject& vao, int bindingIndex) {
    if (!m_initialized) {
        initialize();
    }

    GLint location = program.getAttributeLocation("v_vertex");
    assert(location >= 0);

    glow::VertexAttributeBinding* binding = vao.binding(bindingIndex);
    binding->setAttribute(location);
    binding->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3));
    binding->setFormat(3, GL_FLOAT, GL_FALSE, 0);

    vao.enable(location);
}

void CubeMesh::initialize() {
    //assert(ContextProvider::instance()->available());

    std::array<glm::vec3, 24> array {
        llf, llb, lrb, lrf, llf, lrf, llb, lrb,
        ulf, ulb, urb, urf, ulf, urf, ulb, urb,
        llf, ulf, llb, ulb, lrf, urf, lrb, urb
    };

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(array);

    m_initialized = true;
}

void CubeMesh::beforeContextDestroy() {
    m_vertexBuffer = nullptr;
    m_initialized = false;
}

void CubeMesh::afterContextRebuild() {

}

