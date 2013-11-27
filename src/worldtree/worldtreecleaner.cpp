#include "worldTreecleaner.h"

#include <assert.h>

WorldTreeCleaner::WorldTreeCleaner(WorldTree &worldTree):
    m_worldTree(worldTree)
{

}

WorldTreeCleaner::~WorldTreeCleaner() {

}

void WorldTreeCleaner::invoke() {
    if(m_worldTree.isLeaf()) {
        return;
    }

    invoke(&m_worldTree);
}


void WorldTreeCleaner::invoke(WorldTreeNode *node) {
    assert(!node->isLeaf());

    int geodesInSubnodes = 0;

    for(WorldTreeNode *subnode : node->m_subnodes) {
        if(!subnode->isLeaf()) {
            invoke(subnode);
            if(!subnode->isLeaf()) {
                return;
            }
        }
        geodesInSubnodes += subnode->geodes().size();
    }

    if(geodesInSubnodes <= WorldTreeNode::MAX_GEODES) {
        node->unsplit();
    }
}

