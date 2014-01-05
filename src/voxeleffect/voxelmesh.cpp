#include "voxelmesh.h"

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

glm::vec3 VERTICES[8]
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

glm::vec3 NORMALS[7]
{
    glm::vec3(-1, 0, 0)
        , glm::vec3(1, 0, 0)
        , glm::vec3(0, -1, 0)
        , glm::vec3(0, 1, 0)
        , glm::vec3(0, 0, -1)
        , glm::vec3(0, 0, 1)
        , glm::vec3(0, 0, 0)  // dummy
};

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


const glow::Array<glm::vec3> VoxelMesh::vertices() {
    return glow::Array<glm::vec3>
    {
        VERTICES[7]
            , VERTICES[3]
            , VERTICES[5]
            , VERTICES[1]
            , VERTICES[0]
            , VERTICES[3]
            , VERTICES[2]
            , VERTICES[7]
            , VERTICES[6]
            , VERTICES[5]
            , VERTICES[4]
            , VERTICES[0]
            , VERTICES[6]
            , VERTICES[2]
    };
}

const glow::Array<glm::vec3> VoxelMesh::normals() {
    return glow::Array<glm::vec3>
    {
        NORMALS[6]
            ,  NORMALS[6]
            ,  NORMALS[5]
            , NORMALS[5]
            ,  NORMALS[2]
            ,  NORMALS[0]
            ,  NORMALS[0]
            ,  NORMALS[3]
            ,  NORMALS[3]
            ,  NORMALS[1]
            ,  NORMALS[1]
            , NORMALS[2]
            ,  NORMALS[4]
            , NORMALS[4]
    };
}

