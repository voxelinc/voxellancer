#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class ClusterLoader {

public:
	ClusterLoader();
	void loadClusterFromFile(char* filename, void* Voxelcluster);

private:
	void readDimensions(int* x, int* y, int* z);

private:
	std::ifstream* inputStream;
};