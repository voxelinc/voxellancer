#include "worldtreerenderer.h"

#include "utils/aabbrenderer.h"

#include "world/world.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"


WorldTreeRenderer::WorldTreeRenderer():
    m_renderer(new AABBRenderer())
{
}

WorldTreeRenderer::~WorldTreeRenderer() = default;

void WorldTreeRenderer::draw(const Camera& camera) {
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
