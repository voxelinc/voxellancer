#include "clusterloader.h"

#include <sstream>

#include "voxel/voxelcluster.h"


ClusterLoader::ClusterLoader()
{

}

void ClusterLoader::load(const std::string &filename, std::vector<Voxel*> *list){
	m_inputStream = new std::ifstream(filename, std::ios::in | std::ios::binary);

	if (m_inputStream->fail())
		throw std::runtime_error("file " + std::string(filename) + " not found");

	std::vector<std::string> filenameParts;
	splitStr(filename, '.', filenameParts);
	std::string extension = filenameParts[1];
	if (extension.compare("csv") == 0)
		loadCsv(list);
	else if (extension.compare("zox") == 0)
		loadZox(list);

}

void ClusterLoader::loadCsv(std::vector<Voxel*> *list){
	readDimensionsCsv();
	readCsv(list);
}

void ClusterLoader::loadZox(std::vector<Voxel*> *list){
	
	std::string content;
	m_inputStream->seekg(0, m_inputStream->end);
	content.resize(m_inputStream->tellg());
	m_inputStream->seekg(0, std::ios::beg);
	m_inputStream->read(&content[0], content.size());
	m_inputStream->close();

	readZox(content, list);
	return;
}

void ClusterLoader::readZox(std::string &content, std::vector<Voxel*> *list){
	int begin = content.find("{\"frames\": ");
	int end = content.find(",");
	int frameCount = stoi(content.substr(begin + 11, end - (begin + 11)));
	int currentFrame = 0;
	int position = 0;
	std::string frame, voxelString;
	std::vector<std::string> voxelStrings;
	unsigned int color, r, g, b, a;
	while (currentFrame < frameCount){
		frame = "\"frame" + std::to_string(currentFrame + 1) + "\": [";
		position = content.find(frame) + frame.size();
		while (content.at(position) == '['){
			end = content.find_first_of("]", position + 1);
			voxelString = content.substr(position + 1, end - (position + 1));
			position = end + 3;
			voxelStrings.clear();
			splitStr(voxelString, ',', voxelStrings);
			std::string str = &(voxelStrings[3])[1];
			color = stoul(str);
			r = (color & 0xFF000000) >> 24;
			g = (color & 0x00FF0000) >> 16;
			b = (color & 0x0000FF00) >> 8;
			a = (color & 0x000000FF);
            list->push_back(new Voxel(cvec3(stoi(voxelStrings[0]), std::stoi(&(voxelStrings[1])[1]), std::stoi(&(voxelStrings[2])[1])), cvec3(r, g, b)));
		}
		currentFrame++;
	}

}

void ClusterLoader::readDimensionsCsv(){
	std::string line;
	getline(*m_inputStream, line);

	std::vector<std::string> subStrings;
	splitStr(line, ',', subStrings);

	x = stoi(subStrings[0]);
	y = stoi(subStrings[1])-1;
	z = stoi(subStrings[2]);
}

void ClusterLoader::readCsv(std::vector<Voxel*> *list){
	int red, green, blue;
    glm::ivec3 cell(0, 0, 0);
	std::string line;
	std::vector<std::string> voxelStrings;
	cell.y = y;
	while (cell.y > -1){
		cell.z = 0;
		while (cell.z < z){
			cell.x = 0;
			getline(*m_inputStream, line);
			voxelStrings.clear();
			splitStr(line, ',', voxelStrings);
			while (cell.x < x){
				red = stoi(voxelStrings[cell.x].substr(1, 2), NULL, 16);
				green = stoi(voxelStrings[cell.x].substr(3, 2), NULL, 16);
				blue = stoi(voxelStrings[cell.x].substr(5, 2), NULL, 16);
				if (red+green+blue>0)
                    list->push_back(new Voxel(cvec3(cell), cvec3(red, green, blue)));
				cell.x++;
			}
			cell.z++;
		}
		getline(*m_inputStream, line);
		cell.y--;
	}

}
void ClusterLoader::splitStr(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::istringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
