#pragma once

#include <list>
#include <vector>
#include <memory>


class SplitData;
class WorldObject;

class Splitter {
public:
    void split(std::vector<std::shared_ptr<SplitData>> &splits);


protected:
    void performSplit(std::shared_ptr<SplitData> split);
};

