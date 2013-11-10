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
	void readDimensionsCsv();
	void readClusterCsv(Voxelcluster* cluster);
	void splitStr(const string &s, char delim, vector<string> &elems);
	void loadCsv(Voxelcluster* cluster);
	void loadZox(Voxelcluster* cluster);

private:
	std::ifstream* inputStream;
	int x, y, z;
};