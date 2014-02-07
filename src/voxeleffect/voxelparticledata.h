#pragma once

#include <iostream>
#include <stdint.h>


struct VoxelParticleData {
    VoxelParticleData():
        dead(true),
        deathTime(0.0f) // The particle never lived
    {
    }

    /*
        Yes, this constructor may seem like overhead, but it will not take long for the member order to be changed
        and hard to track errors would occur if we wouldn't have it
    */
    VoxelParticleData(  const glm::vec3& creationPosition, const glm::vec3& creationEulers, const glm::vec3& creationDirectionalSpeed,
                        const glm::vec3& creationAngularSpeed, float creationTime, float deathTime, float scale, uint32_t color, float emissiveness,
                        float directinalDampening, float angularDampening):
        dead(false),
        creationPosition(creationPosition),
        creationEulers(creationEulers),
        creationDirectionalSpeed(creationDirectionalSpeed),
        creationAngularSpeed(creationAngularSpeed),
        creationTime(creationTime),
        deathTime(deathTime),
        scale(scale),
        color(color),
        emissiveness(emissiveness),
        directinalDampening(directinalDampening),
        angularDampening(angularDampening)
    {
    }

    bool dead;

    glm::vec3 creationPosition;
    glm::vec3 creationEulers;
    glm::vec3 creationDirectionalSpeed;
    glm::vec3 creationAngularSpeed;
    float creationTime;
    float deathTime;
    float scale;
    uint32_t color;
    float emissiveness;
    float directinalDampening;
    float angularDampening;
};

