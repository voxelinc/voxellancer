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
class WorldObjectHandle;
class Sound;
class BoardComputer;

class Ship : public WorldObject {
public:
    Ship();
    virtual void update(float deltaSec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint* hardpoint);
    virtual void addEngineVoxel(EngineVoxel* voxel);


    void removeEngine(Engine* engine);

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();
    void fireAtPoint(glm::vec3 target);
    void fireAtObject();
    float minAimDistance();
    BoardComputer* boardComputer();

    virtual void accelerate(const glm::vec3& direction) override;
    virtual void accelerateAngular(const glm::vec3& axis) override;

    void setCharacter(Character* character);
    Character* character();
    void setEngineSound(std::shared_ptr<Sound> sound);

protected:
    std::unique_ptr<Character> m_character;
    std::unique_ptr<BoardComputer> m_boardComputer;
    std::shared_ptr<Sound> m_sound;
    glm::vec3 m_enginePos;

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    std::list<Hardpoint*> m_hardpoints;
    std::list<Engine*> m_engines;

    std::shared_ptr<WorldObjectHandle> m_targetObjectHandle;

    void updateEnginePosition();

};
