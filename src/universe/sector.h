#pragma once

#include <list>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>

#include "utils/component.h"

#include "worldobject/worldobject.h"

#include "functionalobject.h"


class Camera;
template<typename> class GameObjectManager;
class SectorLogic;
class Skybox;
class Universe;
class VoxelParticleEngine;
class VoxelRenderer;
class WorldObjectManager;
class WorldTree;

class Sector {
public:
    Sector(const std::string& name, Universe& universe);
    virtual ~Sector();

    const std::string& name() const;
    Universe& universe();

    WorldTree& worldTree();
    VoxelParticleEngine& particleEngine();

    std::list<glow::ref_ptr<FunctionalObject>>& functionalObjects();
    std::list<glow::ref_ptr<WorldObject>>& worldObjects();

    void addFunctionalObject(FunctionalObject* object);

    bool canAddWorldObject(const WorldObject* object) const;
    void addWorldObject(WorldObject* object);

    void update(float deltaSec);

    void draw(const Camera& camera);


protected:
    std::string m_name;
    Universe& m_universe;

    Component<WorldTree> m_worldTree;

    Component<GameObjectManager<FunctionalObject>> m_functionalObjects;
    Component<WorldObjectManager> m_worldObjects;

    Component<Skybox> m_skybox;
    Component<VoxelParticleEngine> m_particleEngine;
    Component<SectorLogic> m_sectorLogic;

    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    glm::vec3 m_lightDir;
};

