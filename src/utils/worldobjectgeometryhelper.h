#pragma once

#include <vector>
#include <unordered_set>


class WorldObject;
template<class T> class Handle;

class WorldObjectGeometryHelper {
public:
    // Return the WorldObject from objects that is closest to self, measured position to position
    static WorldObject* closestObject(WorldObject& self, std::unordered_set<WorldObject*>* objects);
    static WorldObject* closestObject(WorldObject& self, std::vector<Handle<WorldObject>>* objects);

};

