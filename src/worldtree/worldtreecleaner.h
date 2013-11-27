#pragma once

#include "worldtree.h"
#include "worldtreenode.h"


class WorldTreeCleaner
{
public:
    WorldTreeCleaner(WorldTree &worldTree);
    virtual ~WorldTreeCleaner();

    void invoke();


protected:
    WorldTree &m_worldTree;

    void invoke(WorldTreeNode *node);
};
