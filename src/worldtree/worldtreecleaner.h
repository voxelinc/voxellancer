#pragma once

#include "worldTree.h"
#include "worldTreenode.h"


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
