#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "voxel/voxel.h"
#include "colorcoder.h"

class VoxelCluster;

class ClusterLoader {

public:
	ClusterLoader();
	void load(const std::string &filename, std::vector<Voxel*> *list);

private:
	void readDimensionsCsv();
    void readCsv(std::vector<Voxel*> *list);
	void splitStr(const std::string &s, char delim, std::vector<std::string> &elems);
    void loadCsv(std::vector<Voxel*> *list);
    void loadZox(std::vector<Voxel*> *list);
    void readZox(std::string &content, std::vector<Voxel*> *list);
    void addVoxel(cvec3 gridCell, cvec3 color, std::vector<Voxel*> *list);

private:
    ColorCoder m_colorCoder;
	std::ifstream* m_inputStream;
	int x, y, z;
};