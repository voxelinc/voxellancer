#pragma once

#include <list>
#include <unordered_set>

#include <glow/ref_ptr.h>


class Sector;
class WorldObject;

class GarbageCollector final {
public:
    GarbageCollector(Sector& sector);

    void check();


protected:
    Sector& m_sector;
};

