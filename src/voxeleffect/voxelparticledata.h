#pragma once

#include <glm/glm.hpp>

#include <stdint.h>

struct VoxelParticleData {
    enum class Status { Removed, Alive, Dead };

    VoxelParticleData():
        status(Status::Removed),
        deathTime(0.0f)
    {
    }

    // Extra attribute, not necessarily used by the shader
    Status status;

    glm::vec3 creationPosition;
    glm::vec3 creationEulers;
    glm::vec3 directionalSpeed;
    glm::vec3 angularSpeed;
    float creationTime;
    float deathTime;
    float creationScale;
    float deathScale;
    uint32_t creationColor;
    uint32_t deathColor;
    float emissiveness;
};

