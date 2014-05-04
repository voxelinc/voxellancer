#pragma once

#include <memory>
#include <unordered_set>

#include "utils/component.h"


class EventPoller;
class FactionMatrix;
class God;
class MissionSystem;
class Player;
class Ship;
class Skybox;
class ScriptEngine;
class VoxelParticleEngine;
class WorldObject;
class WorldLogic;
class WorldTree;

class World {
public:
    World();
    virtual ~World();

    Player& player();
    Skybox& skybox();
    WorldLogic& worldLogic();
    God& god();
    WorldTree& worldTree();
    ScriptEngine& scriptEngine();
    VoxelParticleEngine& particleEngine();
    FactionMatrix& factionMatrix();
    EventPoller& eventPoller();
    MissionSystem& missionSystem();

    std::unordered_set<WorldObject*>& worldObjects();
    std::unordered_set<Ship*>& ships();

    void printStatus();

    void update(float deltaSecs);

    float deltaSec() const;

    static World* instance();
    static void reset(bool showWarning=true);


protected:
    friend class God;

    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);

protected:
    static World* s_instance;

    float m_deltaSec;

    Component<Player> m_player;
    Component<ScriptEngine> m_scriptEngine;
    Component<Skybox> m_skybox;
    Component<WorldTree> m_worldTree;
    Component<WorldLogic> m_worldLogic;
    Component<God> m_god;
    Component<VoxelParticleEngine> m_particleEngine;
    Component<FactionMatrix> m_factionMatrix;
    Component<EventPoller> m_eventPoller;
    Component<MissionSystem> m_missionSystem;

    std::unordered_set<WorldObject*> m_worldObjects;
    std::unordered_set<Ship*> m_ships;
};

