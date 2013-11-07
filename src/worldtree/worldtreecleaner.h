#pragma once

#include "worldtree.h"
#include "worldtreenode.h"


class WorldtreeCleaner
{
public:
    WorldtreeCleaner(Worldtree &worldtree);
    virtual ~WorldtreeCleaner();

    void invoke();


protected:
    Worldtree &m_worldtree;

    void invoke(WorldtreeNode *node);
};
