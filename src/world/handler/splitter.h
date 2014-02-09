#pragma once

#include <list>
#include <vector>
#include <memory>

class SplitData;
class WorldObject;

class Splitter
{
public:
    void split(std::vector<std::shared_ptr<SplitData>> &splits);
    std::list<WorldObject*> &splitOffWorldObjects();


protected:
    std::list<WorldObject*> m_splitOffWorldObjects;

    WorldObject *createWorldObjectFromSplitOff(std::shared_ptr<SplitData> split);
    void removeExtractedVoxelsFromEx(std::shared_ptr<SplitData> split);
};

