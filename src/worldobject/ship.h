#pragma once

#include <list>
#include <memory>

#include "worldobject.h"
#include "property/property.h"


class World;
class God;
class Hardpoint;
class Engine;
class Character;
class Sound;
class SquadLogic;
class BoardComputer;

class Ship : public WorldObject {
public:
    Ship();
    virtual ~Ship();

    virtual void update(float deltaSec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint* hardpoint);
    const std::list<Hardpoint*> hardpoints() const;

    virtual void addEngineVoxel(EngineVoxel* voxel);

    Handle<Ship> shipHandle();

    void removeEngine(Engine* engine);

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();

    void fireAtPoint(glm::vec3 target);
    void fireAtObject();
    float minAimDistance();
    float maxAimDistance();
    BoardComputer* boardComputer();
    SquadLogic* squadLogic();

    virtual void accelerate(const glm::vec3& direction) override;
    virtual void accelerateAngular(const glm::vec3& axis) override;

    void setCharacter(Character* character);
    Character* character();
    void setEngineSound(std::shared_ptr<Sound> sound);


protected:
    Ship(CollisionFilter* collisionFilter);

    std::unique_ptr<Character> m_character;
    std::unique_ptr<BoardComputer> m_boardComputer;
    std::unique_ptr<SquadLogic> m_squadLogic;
    std::shared_ptr<Sound> m_sound;
    glm::vec3 m_enginePos;

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    std::list<Hardpoint*> m_hardpoints;
    std::list<Engine*> m_engines;

    Handle<Ship> m_shipHandle;
    Handle<WorldObject> m_targetObjectHandle;

    void updateEnginePosition();
};
