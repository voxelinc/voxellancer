#pragma once


template<typename WorldObjectType>
WorldObjectType* WorldObjectBuilder::newWorldObject() {
	WorldObjectType* worldObject = new WorldObjectType();

	setupVoxelCluster(worldObject);
    setupComponents(worldObject->components());

    return worldObject;
}

