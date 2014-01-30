#pragma once


class WorldObject;
class EngineVoxel;
class HardpointVoxel;

class WorldObjectComponents {
public:
    WorldObjectComponents(WorldObject* worldObject);

    void addEngineVoxel(EngineVoxel* voxel);
    void removeEngineVoxel(EngineVoxel* voxel);

    void addHardpointVoxel(HardpointVoxel* voxel);
    void addCockpitVoxel(CockpitVoxel* voxel);
    void addFuelVoxel(FuelVoxel* voxel);
};

