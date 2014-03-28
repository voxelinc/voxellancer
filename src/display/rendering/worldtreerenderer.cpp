#include "worldtreerenderer.h"

#include "utils/aabbrenderer.h"

#include "world/world.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"


WorldTreeRenderer::WorldTreeRenderer()
{
}

WorldTreeRenderer::~WorldTreeRenderer() = default;

void WorldTreeRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    m_renderer->clear();

    WorldTreeNode* root = World::instance()->worldTree().root();
    poll(root);

    m_renderer->draw(camera);
}

void WorldTreeRenderer::poll(WorldTreeNode* node) {
    if (node->isLeaf()) {
        m_renderer->add(node->aabb());
    } else {
        for (WorldTreeNode* subnode : node->subnodes()) {
            poll(subnode);
        }
    }
}

void WorldTreeRenderer::initialize() {
    m_renderer.reset(new AABBRenderer());
    m_initialized = true;
}

