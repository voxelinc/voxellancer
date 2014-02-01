#pragma once

#include "components/acceleration.h"


class EngineSlot;
class Hardpoint;
class HardpointVoxel;
class WorldObject;

/*
    Module of the WorldObject that is responsible for managing all
    the components of a WorldObject (Engines, Weapons) and their respective
    slots.
    Also provides functions to trigger actions or retrieve values from
    a whole category of components. (like, fire all weapons, set all engines)
*/
class WorldObjectComponents {
public:
    WorldObjectComponents(WorldObject* worldObject);

    WorldObject* worldObject();

    void addEngineSlot(EngineSlot* engineSlot);
    void removeEngineSlot(EngineSlot* engineSlot);

    /*
        Access EngineSlots either by index in the model or all of them
        at a time
    */
    EngineSlot* engineSlot(int index);
    std::list<EngineSlot*>& engineSlots();

    /*
        Poll all installed engines for accumulated Acceleration
    */
    Acceleration maxAcceleration() const;

    /*
        Set relative Acceleration on all installed engines
    */
    const Acceleration& currentRelativeAcceleration() const;
    void setCurrentRelativeAcceleration(const Acceleration& currentRelativeAcceleration);


    void addHardpoint(Hardpoint* hardpoint);
    void removeHardpoint(Hardpoint* hardpoint);

    /*
        Access Hardpoints either by index in the model or all of them
        at a time
    */
    Hardpoint* hardpoint(int index);
    std::list<Hardpoint*>& hardpoints();

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

    std::list<EngineSlot*> m_engineSlots;
    std::list<Hardpoint*> m_hardpoints;

    Acceleration m_currentRelativeAcceleration;
};

