#include "voxelmesh.h"
#include <glow/Buffer.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>

static const glm::vec3 llf(-.5f, -.5f, -.5f);
static const glm::vec3 llb(-.5f, -.5f, .5f);
static const glm::vec3 luf(-.5f, .5f, -.5f);
static const glm::vec3 lub(-.5f, .5f, .5f);
static const glm::vec3 rlf(.5f, -.5f, -.5f);
static const glm::vec3 rlb(.5f, -.5f, .5f);
static const glm::vec3 ruf(.5f, .5f, -.5f);
static const glm::vec3 rub(.5f, .5f, .5f);

static const glm::vec3 left(-1, 0, 0);
static const glm::vec3 right(1, 0, 0);
static const glm::vec3 bottom(0, -1, 0);
static const glm::vec3 top(0, 1, 0);
static const glm::vec3 front(0, 0, -1);
static const glm::vec3 back(0, 0, 1);
static const glm::vec3 dummy(0, 0, 0) ;

glow::Array<glm::vec3> VoxelMesh::s_vertices
{
    rub,
    lub,
    rlb,
    llb,
    llf,
    lub,
    luf,
    rub,
    ruf,
    rlb,
    rlf,
    llf,
    ruf,
    luf
};

glow::Array<glm::vec3> VoxelMesh::s_normals
{
    dummy, dummy,
    back, back,
    bottom,
    left, left,
    top, top,
    right, right,
    bottom,
    front, front
};

glow::ref_ptr<glow::Buffer> VoxelMesh::s_vertexBuffer = nullptr;


void VoxelMesh::initBuffer() {
    glm::vec3 vertices[8]
    {
        glm::vec3(-.5f, -.5f, -.5f)
        , glm::vec3(-.5f, -.5f, .5f)
        , glm::vec3(-.5f, .5f, -.5f)
        , glm::vec3(-.5f, .5f, .5f)
        , glm::vec3(.5f, -.5f, -.5f)
        , glm::vec3(.5f, -.5f, .5f)
        , glm::vec3(.5f, .5f, -.5f)
        , glm::vec3(.5f, .5f, .5f)
    };

    glm::vec3 normals[7]
    {
        glm::vec3(-1, 0, 0)
        , glm::vec3(1, 0, 0)
        , glm::vec3(0, -1, 0)
        , glm::vec3(0, 1, 0)
        , glm::vec3(0, 0, -1)
        , glm::vec3(0, 0, 1)
        , glm::vec3(0, 0, 0)  // dummy
    };

    glow::Array<glm::vec3> arr{
        vertices[7], normals[6]
        , vertices[3], normals[6]
        , vertices[5], normals[5]
        , vertices[1], normals[5]
        , vertices[0], normals[2]
        , vertices[3], normals[0]
        , vertices[2], normals[0]
        , vertices[7], normals[3]
        , vertices[6], normals[3]
        , vertices[5], normals[1]
        , vertices[4], normals[1]
        , vertices[0], normals[2]
        , vertices[6], normals[4]
        , vertices[2], normals[4]
    };

    s_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    s_vertexBuffer->setData(arr);
}

glow::ref_ptr<glow::Buffer> VoxelMesh::vertexBuffer() {
    if (!s_vertexBuffer) {
        initBuffer();
    }
    return s_vertexBuffer;
}

void VoxelMesh::bindTo(
    glow::ref_ptr<glow::Program> program, 
    glow::ref_ptr<glow::VertexArrayObject> vao, 
    int index) 
{
    auto binding0 = vao->binding(index);
    auto a_vertex = program->getAttributeLocation("v_vertex");

    binding0->setAttribute(a_vertex);
    binding0->setBuffer(vertexBuffer(), 0, sizeof(glm::vec3) * 2);
    binding0->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    vao->enable(a_vertex);

    auto binding1 = vao->binding(index+1);
    auto a_normal = program->getAttributeLocation("v_normal");
    binding1->setAttribute(a_normal);
    binding1->setBuffer(vertexBuffer(), 0, sizeof(glm::vec3) * 2);
    binding1->setFormat(3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3));
    vao->enable(a_normal);
}

void VoxelMesh::tearDown() {
    s_vertexBuffer = nullptr;
}

