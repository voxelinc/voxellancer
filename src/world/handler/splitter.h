#pragma once

#include <list>

class SplitData;
class WorldObject;

class Splitter
{
public:
    void split(std::list<SplitData*> &splits);
    std::list<WorldObject*> &splitOffWorldObjects();


protected:
    std::list<WorldObject*> m_splitOffWorldObjects;

    WorldObject *createWorldObjectFromSplitOff(SplitData *split);
    void removeExtractedVoxelsFromEx(SplitData *split);
};

