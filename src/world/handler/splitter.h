#pragma once

#include <list>

class WorldObjectSplit;
class WorldObject;

class Splitter
{
public:
    void split(std::list<WorldObjectSplit*> &splits);
    std::list<WorldObject*> &splitOffWorldObjects();


protected:
    std::list<WorldObject*> m_splitOffWorldObjects;

    WorldObject *createWorldObjectFromOrphan(WorldObjectSplit *split);
    void removeExtractedVoxelsFromEx(WorldObjectSplit *split);
};

