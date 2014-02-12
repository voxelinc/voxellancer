#pragma once

#include <memory>

#include <glm/glm.hpp>


class Ship;
class EngineVoxel;
class EngineTrailGenerator;

class Engine {
public:
    Engine(Ship* Ship, EngineVoxel* voxel);
    ~Engine();

    glm::vec3 positionInGrid() const;
    glm::vec3 position() const;
    Ship* ship();

    void update(float deltaSec);

    void voxelRemoved();
private:
    std::unique_ptr<EngineTrailGenerator> m_generator;
    glm::vec3 m_positionInGrid;
    Ship* m_ship;
    float m_cooldown;
};
