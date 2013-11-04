#include "worldtreecleaner.h"

#include <assert.h>

WorldtreeCleaner::WorldtreeCleaner(Worldtree &worldtree):
    m_worldtree(worldtree)
{

}

WorldtreeCleaner::~WorldtreeCleaner() {

}

void WorldtreeCleaner::invoke() {
    if(m_worldtree.isLeaf()) {
        return;
    }

    invoke(&m_worldtree);
}


void WorldtreeCleaner::invoke(WorldtreeNode *node) {
    assert(!node->isLeaf());

    int geodesInSubnodes = 0;

    for(WorldtreeNode *subnode : node->m_subnodes) {
        if(!subnode->isLeaf()) {
            invoke(subnode);
            if(!subnode->isLeaf()) {
                return;
            }
        }
        geodesInSubnodes += subnode->geodes().size();
    }

    if(geodesInSubnodes <= WorldtreeNode::MAX_GEODES) {
        node->unsplit();
    }
}

