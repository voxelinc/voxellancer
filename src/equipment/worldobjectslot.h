#pragma once

#include <map>
#include <list>
#include <string>

#include <glm/glm.hpp>

class SpecialVoxel;
class WorldObjectComponents;

/*
    Base class for everything on a worldobject that behaves like a slot
    that can be (or cannot) be equipped with equipment
*/
class WorldObjectSlot {
public:
    WorldObjectSlot(WorldObjectComponents* components, const SpecialVoxel* specialVoxel, int index);

    std::list<std::string> mountables() const;

    glm::vec3 position();

    bool mountable(const std::string& name) const;
    void setMountable(const std::string& name, bool mountable);

    WorldObjectComponents* components();

    int index() const;


protected:
    WorldObjectComponents* m_components;
    std::map<std::string, bool> m_mountables;
    const SpecialVoxel* m_voxel;
    int m_index;
};

