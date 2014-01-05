#pragma once

#include <glow/Array.h>

#include <glm/glm.hpp>


class VoxelMesh {
public:
    static const glow::Array<glm::vec3> vertices();
    static const glow::Array<glm::vec3> normals();


protected:
    static glow::Array<glm::vec3> s_vertices;
    static glow::Array<glm::vec3> s_normals;
};

