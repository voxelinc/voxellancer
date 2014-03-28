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
    m_initialized(false);
{

}

void CubeMesh::bindLinestripTo(glow::Program& program, glow::VertexArrayBinding* vertexBinding) {
    if (!m_initialized) {
        initialize();
    }
}

void CubeMesh::initialize() {
    //assert(ContextProvider::instance()->available());

    glow::Array<glm::vec3> array{
        llf, llb, lrb, lrf,
        ulf, ulb, urb, urf,


    };

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(array);

    m_initialized = true;
}
