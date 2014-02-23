#pragma once

#include <map>
#include <list>
#include <string>


class WorldObjectComponents;

/*
    Base class for everything on a worldobject that behaves like a slot
    that can be (or cannot) be equipped with equipment
*/
class WorldObjectSlot {
public:
    WorldObjectSlot(WorldObjectComponents* components, int index);

    std::list<std::string> mountables() const;

    bool mountable(const std::string& name) const;
    void setMountable(const std::string& name, bool mountable);

    WorldObjectComponents* components();

    int index() const;


protected:
    WorldObjectComponents* m_components;
    std::map<std::string, bool> m_mountables;
    int m_index;
};

