#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>


class FunctionalWorldElement;
class PhysicalWorldElement;
class Skybox;
class Universe;
class WorldTree;

class Sector {
public:
    Sector(const std::string& name, Universe* universe);
    virtual ~Sector();

    const std::string& name() const;
    Universe* universe();

    WorldTree& worldTree();

    std::list<glow::ref_ptr<FunctionalWorldElement>>& functionalElements();
    std::list<glow::ref_ptr<FunctionalWorldElement>>& physicalElements();

    void addElement(FunctionalWorldElement* element);
    void addElement(PhysicalWorldElement* element);

    void update(float deltaSec);

    void draw(const Camera& camera);


protected:
    std::string m_name;
    Universe* m_universe;

    std::unique_ptr<WorldTree> m_worldTree;

    std::list<glow::ref_ptr<UniverseElements>> m_functionalElements;
    std::list<glow::ref_ptr<PhysicalWorldElement>> m_physicalElements;

    std::unique_ptr<Skybox> m_skybox;
    glm::vec3 m_lightDir;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
};

