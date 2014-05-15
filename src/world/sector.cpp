#include "sector.h"

#include "display/rendering/skybox.h"

#include "voxel/voxelrenderer.h"

#include "worldtree/worldtree.h"


Sector::Sector(const std::string& name, Universe* universe):
    m_name(name),
    m_universe(universe),
    m_worldTree(new WorldTree()),
    m_skybox(new Skybox()),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_lightDir(0.3f, 0.5f, 1.0f)
{

}

Sector::~Sector() = default;

const std::string& Sector::name() const {
    return m_name;
}

Universe* Sector::universe() {
    return m_universe;
}

WorldTree& Sector::worldTree() {
    return m_worldTree;
}

std::list<glow::ref_ptr<FunctionalWorldElement>>& Sector::functionalElements(){

}

std::list<glow::ref_ptr<FunctionalWorldElement>>& Sector::physicalElements() {

}


void Sector::addElement(FunctionalWorldElement* element) {

}

void Sector::addElement(PhysicalWorldElement* element){

}

void Sector::update(float deltaSec) {

}

void Sector::draw(const Camera& camera) {
    m_voxelRenderer->program()->setUniform("lightdir", m_defaultLightDir.get());

    m_voxelRenderer->prepareDraw(camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(*worldObject);
    }

    m_voxelRenderer->afterDraw();

    World::instance()->particleEngine().draw(camera);
}

