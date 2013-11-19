#pragma once

#include <fstream>
#include <string>
#include <vector>

class VoxelCluster;

class ClusterLoader {

public:
	ClusterLoader();
	void loadClusterFromFile(char* filename, VoxelCluster* voxelcluster);

private:
	void readDimensionsCsv();
	void readClusterCsv(VoxelCluster* cluster);
	void splitStr(const std::string &s, char delim, std::vector<std::string> &elems);
	void loadCsv(VoxelCluster* cluster);
	void loadZox(VoxelCluster* cluster);
	void readClusterZox(std::string content, VoxelCluster* cluster);

private:
	std::ifstream* inputStream;
	int x, y, z;
};