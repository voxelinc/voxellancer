#include "clusterloader.h"

using namespace std;

ClusterLoader::ClusterLoader(){

}

void ClusterLoader::loadClusterFromFile(char* filename, void* Voxelcluster){
	inputStream = new ifstream(filename);
	int x, y, z;
	readDimensions(&x, &y, &z);
}

void ClusterLoader::readDimensions(int* x, int* y, int* z){
	string line;
	getline(*inputStream, line);

	char * dimensions = new char[line.length() + 1];
	std::strcpy(dimensions, line.c_str());

	char* tmp = strtok(dimensions, ",");
	*x = atoi(tmp);
	tmp = strtok(NULL, ",");
	*y = atoi(tmp);
	tmp = strtok(NULL, ",");
	*z = atoi(tmp);
}

