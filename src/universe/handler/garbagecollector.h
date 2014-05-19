#pragma once

#include <list>
#include <unordered_set>

#include <glow/ref_ptr.h>

class WorldObject;

class GarbageCollector {
public:
    void check(std::list<glow::ref_ptr<WorldObject>>& objects);
};

