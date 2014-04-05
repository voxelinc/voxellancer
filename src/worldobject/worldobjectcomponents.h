#pragma once

#include <list>
#include <memory>

#include "equipment/enginepower.h"
#include "equipment/enginestate.h"
#include "geometry/speed.h"


class EngineSlot;
class Hardpoint;
class HardpointVoxel;
class WorldObject;

/**
 *   Module of the WorldObject that is responsible for managing all
 *   the components of a WorldObject (Engines, Weapons) and their respective
 *   slots.
 *   Also provides functions to trigger actions or retrieve values from
 *   a whole category of components. (like, fire all weapons, set all engines)
*/
class WorldObjectComponents {
public:
    WorldObjectComponents(WorldObject* worldObject);

    WorldObject* worldObject();
    const WorldObject* worldObject() const;

    void addEngineSlot(std::shared_ptr<EngineSlot> engineSlot);
    void removeEngineSlot(const EngineSlot* engineSlot);

    /*
        Access EngineSlots either by index in the model or all of them
        at a time
    */
    std::shared_ptr<EngineSlot> engineSlot(int index);
    std::list<std::shared_ptr<EngineSlot>>& engineSlots();

    EnginePower maxSpeed() const;
    void setMaxSpeed(const EnginePower& maxSpeed);

    Acceleration currentAcceleration();

    const EngineState& engineState() const;
    void setEngineState(const EngineState& engineState);


    void addHardpoint(std::shared_ptr<Hardpoint> hardpoint);
    void removeHardpoint(const Hardpoint* hardpoint);

    /*
        Access Hardpoints either by index in the model or all of them
        at a time
    */
    std::shared_ptr<Hardpoint> hardpoint(int index);
    std::list<std::shared_ptr<Hardpoint>>& hardpoints();

    /*
        Fire all installed weapons either at a point or a WorldObject
        What of both will actually trigger an action depends on the weapons
        aimType
    */
    void fireAtPoint(const glm::vec3& point);
    void fireAtObject(WorldObject* worldObject);

    /*
        Update all components
    */
    void update(float deltaSec);



protected:
    WorldObject* m_worldObject;

    std::list<std::shared_ptr<EngineSlot>> m_engineSlots;
    std::list<std::shared_ptr<Hardpoint>> m_hardpoints;

    EngineState m_engineState;
    EnginePower m_maxSpeed;
};

