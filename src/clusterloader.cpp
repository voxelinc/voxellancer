#include "clusterloader.h"

using namespace std;

ClusterLoader::ClusterLoader(){

}

void ClusterLoader::loadClusterFromFile(char* filename, Voxelcluster* voxelcluster){
	inputStream = new ifstream(filename);
	vector<string> filenameParts;
	splitStr(filename, '.', filenameParts);
	string extension = filenameParts[1];
	if (extension.compare("csv") == 0)
		loadCsv(voxelcluster);
	else if (extension.compare("zox") == 0)
		loadZox(voxelcluster);

}

void ClusterLoader::loadCsv(Voxelcluster* cluster){
	readDimensionsCsv();
	readClusterCsv(cluster);
}

void ClusterLoader::loadZox(Voxelcluster* cluster){
	//TODO implement zox parser
}

void ClusterLoader::readDimensionsCsv(){
	string line;
	getline(*inputStream, line);

	vector<string> subStrings;
	splitStr(line, ',', subStrings);

	x = stoi(subStrings[0]);
	y = stoi(subStrings[1])-1;
	z = stoi(subStrings[2]);
}

void ClusterLoader::readClusterCsv(Voxelcluster *cluster){
	int alpha, red, green, blue, currentX, currentZ, currentY;
	string line;
	currentY = y;
	while (currentY > -1){
		currentX = 0;
		while (currentX < x){
			currentZ = 0;
			getline(*inputStream, line);
			vector<string> voxelStrings;
			splitStr(line, ',', voxelStrings);
			while (currentZ < z){
				red = stoi(voxelStrings[currentZ].substr(3, 2), NULL, 16);
				green = stoi(voxelStrings[currentZ].substr(5, 2), NULL, 16);
				blue = stoi(voxelStrings[currentZ].substr(7, 2), NULL, 16);
				if (red+green+blue>0)
					cluster->addVoxel(Voxel(cvec3(currentX, currentY, currentZ), ucvec3(red, green, blue)));
				currentZ++;
			}
			currentX++;
		}
		getline(*inputStream, line);
		currentY--;
	}

}

void ClusterLoader::splitStr(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
