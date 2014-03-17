#pragma once

#include <memory>
#include <unordered_set>


class FactionMatrix;
class God;
class Ship;
class Skybox;
class VoxelParticleEngine;
class WorldObject;
class WorldLogic;
class WorldTree;
class TextFieldHudget;
class HUD;

class World {
public:
    World();
    virtual ~World();

    Skybox &skybox();
    WorldLogic &worldLogic();
    God &god();
    WorldTree &worldTree();
    VoxelParticleEngine& particleEngine();
    FactionMatrix& factionMatrix();

    std::unordered_set<WorldObject*> &worldObjects();
    std::unordered_set<Ship*> &ships();

    void update(float deltaSecs);

    float deltaSec() const;

    static World *instance();
    static void reset();

    void showText(std::string text, HUD* hud, float lifeTime = 2.0f);


protected:
    friend class God;

    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);


protected:
    static World *s_instance;

    float m_deltaSec;

    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::unique_ptr<VoxelParticleEngine> m_particleEngine;
    std::unique_ptr<FactionMatrix> m_factionMatrix;

    std::unique_ptr<TextFieldHudget> m_textHudget;
    float m_textLifeTime;
    float m_textTimer;
    

    std::unordered_set<WorldObject*> m_worldObjects;
    std::unordered_set<Ship*> m_ships;

};

