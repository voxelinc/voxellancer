#pragma once

#include <list>
#include <memory>
#include <unordered_set>

#include <glow/ref_ptr.h>


class FactionMatrix;
class God;
class Player;
class Ship;
class Skybox;
class ScriptEngine;
class VoxelParticleEngine;
class WorldObject;
class WorldLogic;
class UniverseElement;
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

    std::unordered_set<WorldObject*>& worldObjects();
    std::unordered_set<Ship*>& ships();

    void printStatus();

    void update(float deltaSecs);

    float deltaSec() const;

    static World* instance();

    static void reset(bool showWarning = true);

    void addElement(UniverseElement* element);
    void removeElement(UniverseElement* element);


protected:
    friend class God;

    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);


protected:
    static World* s_instance;

    float m_deltaSec;

    std::unique_ptr<Player> m_player;
    std::unique_ptr<ScriptEngine> m_scriptEngine;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::unique_ptr<VoxelParticleEngine> m_particleEngine;
    std::unique_ptr<FactionMatrix> m_factionMatrix;

    std::list<glow::ref_ptr<UniverseElement>> m_elements;
    std::unordered_set<UniverseElement*> m_scheduledRemovals;

    std::unordered_set<WorldObject*> m_worldObjects;
    std::unordered_set<Ship*> m_ships;
};

