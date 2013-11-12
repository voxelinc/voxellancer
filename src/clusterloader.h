#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class VoxelCluster;

using namespace std;

class ClusterLoader {

public:
	ClusterLoader();
	void loadClusterFromFile(char* filename, VoxelCluster* voxelcluster);

private:
	void readDimensionsCsv();
	void readClusterCsv(VoxelCluster* cluster);
	void splitStr(const string &s, char delim, vector<string> &elems);
	void loadCsv(VoxelCluster* cluster);
	void loadZox(VoxelCluster* cluster);
	void readClusterZox(string content, VoxelCluster* cluster);

private:
	std::ifstream* inputStream;
	int x, y, z;
};