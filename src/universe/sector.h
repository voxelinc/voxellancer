#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>


class FunctionalObject;
template<typename> class GameObjectManager;
class Skybox;
class Universe;
class WorldObject;
class WorldTree;

class Sector {
public:
    Sector(const std::string& name, Universe* universe);
    virtual ~Sector();

    const std::string& name() const;
    Universe* universe();

    WorldTree& worldTree();

    std::list<glow::ref_ptr<FunctionalObject>>& functionalObjects();
    std::list<glow::ref_ptr<WorldObject>>& worldObjects();

    void addFunctionalObject(FunctionalObject* object);
    void addWorldObject(WorldObject* object);

    void update(float deltaSec);

    void draw(const Camera& camera);


protected:
    std::string m_name;
    Universe* m_universe;

    std::unique_ptr<WorldTree> m_worldTree;

    Component<GameObjectManager<FunctionalObject>> m_functionalObjects;
    Component<GameObjectManager<WorldObject>> m_worldObjects;

    Component<Skybox> m_skybox;
    Component<VoxelParticleEngine> m_particleEngine;

    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    glm::vec3 m_lightDir;
};

