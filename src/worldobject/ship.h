#pragma once

#include <list>
#include "worldobject.h"
#include "world/world.h"
#include "world/god.h"
#include "property/propertymanager.h"
#include "property/property.h"
#include "ai/boardcomputer.h"

class World;
class God;
class Hardpoint;
class Engine;
class Character;
class WorldObjectHandle;

class Ship : public WorldObject {
public:
    Ship();

    virtual void update(float deltaSec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint* hardpoint);
    const std::list<Hardpoint*> hardpoints() const;

    virtual void addEngineVoxel(EngineVoxel* voxel);
    void removeEngine(Engine* engine);

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();

    void fireAtPoint(glm::vec3 target);
    void fireAtObject();
    float minAimDistance();

    virtual void accelerate(const glm::vec3& direction) override;
    virtual void accelerateAngular(const glm::vec3& axis) override;

    void setCharacter(Character* character);
    Character* character();


protected:
    std::unique_ptr<Character> m_character;
    BoardComputer m_boardComputer;

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    std::list<Hardpoint*> m_hardpoints;
    std::list<Engine*> m_engines;

    std::shared_ptr<WorldObjectHandle> m_targetObjectHandle;
};
