#include "voxelmesh.h"

#include <glow/Buffer.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>

static const glm::vec4 llf(-0.5f, -0.5f, -0.5f, 0);
static const glm::vec4 llb(-0.5f, -0.5f,  0.5f, 0);
static const glm::vec4 luf(-0.5f,  0.5f, -0.5f, 0);
static const glm::vec4 lub(-0.5f,  0.5f,  0.5f, 0);
static const glm::vec4 rlf( 0.5f, -0.5f, -0.5f, 0);
static const glm::vec4 rlb( 0.5f, -0.5f,  0.5f, 0);
static const glm::vec4 ruf( 0.5f,  0.5f, -0.5f, 0);
static const glm::vec4 urb( 0.5f,  0.5f,  0.5f, 0);

static const glm::vec4 left(-1, 0, 0, 0);
static const glm::vec4 right(1, 0, 0, 1);
static const glm::vec4 bottom(0, -1, 0, 2);
static const glm::vec4 top(0, 1, 0 ,3);
static const glm::vec4 front(0, 0, -1, 4);
static const glm::vec4 back(0, 0, 1, 5);
static const glm::vec4 dummy(0, 0, 0, 0);


VoxelMesh::VoxelMesh():
    m_initialized(false)
{
}

void VoxelMesh::bindTo(
    glow::Program* program,
    glow::VertexArrayObject* vao,
    int bindingIndex)
{
    if(!m_initialized) {
        initialize();
    }

    setupVertexAttribute(program, vao, "v_vertex", GL_FALSE, bindingIndex + 0, 0);
    setupVertexAttribute(program, vao, "v_normal", GL_TRUE,  bindingIndex + 1, sizeof(glm::vec4));
}

void VoxelMesh::initialize() {
    std::array<glm::vec4, 28> array {
        urb, dummy,
        lub, dummy,
        rlb, back,
        llb, back,
        llf, bottom,
        lub, left,
        luf, left,
        urb, top,
        ruf, top,
        rlb, right,
        rlf, right,
        llf, bottom,
        ruf, front,
        luf, front
    };

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(array);

    m_initialized = true;
}

void VoxelMesh::setupVertexAttribute(glow::Program* program, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset) {
    glow::VertexAttributeBinding* binding = vao->binding(bindingNum);
    GLint location = program->getAttributeLocation(name);
    assert(location >= 0);

    binding->setAttribute(location);
    binding->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec4) * 2);
    binding->setFormat(4, GL_FLOAT, normalised, offset);

    vao->enable(location);
}

void VoxelMesh::beforeContextDestroy() {
    m_vertexBuffer = nullptr;
    m_initialized = false;
}

void VoxelMesh::afterContextRebuild() {
    // lazy init
}

