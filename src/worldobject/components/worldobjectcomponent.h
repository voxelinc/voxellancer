#pragma once


class WorldObjectComponents;

/*
    Where the (special)voxels define visual appearance, a WorldObjectComponent
    is responsible for the logic this specialvoxel has.
*/
class WorldObjectComponent {
public:
    WorldObjectComponent(WorldObjectComponents* components, const std::string& name, int index);

    WorldObjectComponents* components();
    const std::string& name();
    int index() const;


protected:
    WorldObjectComponents* m_components;
    std::string m_name;
    int m_index;
};

