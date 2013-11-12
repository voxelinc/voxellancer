#include "clusterloader.h"

using namespace std;

ClusterLoader::ClusterLoader(){

}

void ClusterLoader::loadClusterFromFile(char* filename, VoxelCluster* voxelcluster){
	inputStream = new ifstream(filename, std::ios::in | std::ios::binary);

	if (inputStream->fail())
		throw runtime_error("file " + string(filename) + " not found");

	vector<string> filenameParts;
	splitStr(filename, '.', filenameParts);
	string extension = filenameParts[1];
	if (extension.compare("csv") == 0)
		loadCsv(voxelcluster);
	else if (extension.compare("zox") == 0)
		loadZox(voxelcluster);

}

void ClusterLoader::loadCsv(VoxelCluster* cluster){
	readDimensionsCsv();
	readClusterCsv(cluster);
}

void ClusterLoader::loadZox(VoxelCluster* cluster){
	
	string content;
	inputStream->seekg(0, inputStream->end);
	content.resize(inputStream->tellg());
	inputStream->seekg(0, std::ios::beg);
	inputStream->read(&content[0], content.size());
	inputStream->close();

	readClusterZox(content, cluster);
	return;
}

void ClusterLoader::readClusterZox(string content, VoxelCluster* cluster){
	int begin = content.find("{\"frames\": ");
	int end = content.find(",");
	int frameCount = stoi(content.substr(begin + 11, end - (begin + 11)));
	int currentFrame = 0;
	int position = 0;
	string frame, voxelString;
	vector<string> voxelStrings;
	unsigned int color, r, g, b, a;
	while (currentFrame < frameCount){
		frame = "\"frame" + to_string(currentFrame + 1) + "\": [" ;
		position = content.find(frame) + frame.size();
		while (content.at(position) == '['){
			end = content.find_first_of("]", position + 1);
			voxelString = content.substr(position + 1, end - (position + 1));
			position = end + 3;
			voxelStrings.clear();
			splitStr(voxelString, ',', voxelStrings);
			string str = &(voxelStrings[3])[1];
			color = stoul(str);
			r = (color & 0xFF000000) >> 24;
			g = (color & 0x00FF0000) >> 16;
			b = (color & 0x0000FF00) >> 8;
			a = (color & 0x000000FF);
			cluster->addVoxel(Voxel(cvec3(stoi(voxelStrings[0]), stoi(&(voxelStrings[1])[1]), stoi(&(voxelStrings[2])[1])), ucvec3(r, g, b)));
		}
		currentFrame++;
	}

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

void ClusterLoader::readClusterCsv(VoxelCluster *cluster){
	int red, green, blue, currentZ, currentX, currentY;
	string line;
	vector<string> voxelStrings;
	currentY = y;
	while (currentY > -1){
		currentZ = 0;
		while (currentZ < z){
			currentX = 0;
			getline(*inputStream, line);
			voxelStrings.clear();
			splitStr(line, ',', voxelStrings);
			while (currentX < x){
				red = stoi(voxelStrings[currentX].substr(1, 2), NULL, 16);
				green = stoi(voxelStrings[currentX].substr(3, 2), NULL, 16);
				blue = stoi(voxelStrings[currentX].substr(5, 2), NULL, 16);
				if (red+green+blue>0)
					cluster->addVoxel(Voxel(cvec3(currentX, currentY, currentZ), ucvec3(red, green, blue)));
				currentX++;
			}
			currentZ++;
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
