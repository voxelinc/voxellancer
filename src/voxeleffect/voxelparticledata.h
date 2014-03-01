#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <stdint.h>


class WorldTreeNode;

struct VoxelParticleData {
    VoxelParticleData():
        dead(true),
        worldTreeNode(nullptr),
        deathTime(0.0f) // The particle never lived
    {
    }

    // Extra attributes, not necessarily used by the shader
    bool dead;
    WorldTreeNode* worldTreeNode;

    glm::vec3 creationPosition;
    glm::vec3 creationEulers;
    glm::vec3 directionalSpeed;
    glm::vec3 angularSpeed;
    float creationTime;
    float deathTime;
    float scale;
    uint32_t color;
    float emissiveness;
};

