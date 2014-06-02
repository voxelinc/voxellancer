#pragma once

#include <memory>
#include <string>
#include <unordered_map>


class SectorLoader;
class Universe;

class UniverseLoader {
public:
    UniverseLoader(const std::string& path);
    virtual ~UniverseLoader();

    Universe* universe();


protected:
    std::string m_path;
    std::string m_prefix;

    bool m_loaded;

    Universe* m_universe;

    std::unordered_map<std::string, std::unique_ptr<SectorLoader>> m_sectorLoaders;


    void lazyLoad();
    void loadSectors();
    void connectJumpgates();
};

