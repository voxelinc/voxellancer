#pragma once

#include <map>
#include <string>


class WorldObjectComponents;

/*
    Where the (special)voxels define visual appearance, a WorldObjectSlot
    is responsible for the logic this specialvoxel has.
*/
class WorldObjectSlot {
public:
    WorldObjectSlot(WorldObjectComponents* components, int index);

    bool mountable(const std::string& name) const;
    void setMountable(const std::string& name, bool mountable);

    WorldObjectComponents* components();

    int index() const;


protected:
    WorldObjectComponents* m_components;
    std::map<std::string, bool> m_mountables;
    int m_index;
};

