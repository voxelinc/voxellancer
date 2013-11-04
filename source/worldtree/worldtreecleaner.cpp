#include "worldtreecleaner.h"

#include <assert.h>

WorldtreeCleaner::WorldtreeCleaner(Worldtree &worldtree):
    m_worldtree(worldtree)
{

}

WorldtreeCleaner::~WorldtreeCleaner() {

}

void WorldtreeCleaner::invoke() {
    if(m_worldtreenode.isLeaf()) {
        return;
    }

    invoke(&m_worldtreenode);
}


void WorldtreeCleaner::invoke(WorldtreeNode *node) {
    assert(!m_worldtree.isLeaf());

    int geodesInSubnodes = 0;

    for(const WorldtreeNode *subnode : node->m_sunodes) {
        if(!subnode->isLeaf()) {
            invoke(subnode);
            if(!subnode->isLeaf()) {
                return;
            }
        }
        geodesInSubnodes += subnode->geodes().size();
    }

    if(geodesInSubnodes <= WorldtreeNode::MAX_GEODES) {
        subnode->unsplit();
    }
}

