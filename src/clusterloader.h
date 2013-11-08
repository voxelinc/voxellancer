#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "voxel/voxelcluster.h"
#include "voxel/Voxel.h"

using namespace std;

class ClusterLoader {

public:
	ClusterLoader();
	void loadClusterFromFile(char* filename, Voxelcluster* voxelcluster);

private:
	void readDimensions();
	void readCluster(Voxelcluster* cluster);
	void splitStr(const string &s, char delim, vector<string> &elems);

private:
	std::ifstream* inputStream;
	int x, y, z;
};