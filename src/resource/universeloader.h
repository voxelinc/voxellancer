#pragma once

#include <string>


class Universe;

class UniverseLoader {
public:
    UniverseLoader(const std::string& path);
    virtual ~UniverseLoader();

    Universe* load();


protected:
    std::string m_path;
    std::string m_prefix;
    Universe* m_universe;
    std::unordered_map<std::string, std::shared_ptr<LoadedSector>> m_loadedSectors;

    void loadSectors();
};

