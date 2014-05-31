#pragma once

#include <memory>
#include <string>


class Sector;
class Universe;

class SectorLoader {
public:
    SectorLoader(const std::string& name, const std::string& prefix, Universe& universe);
    virtual ~SectorLoader();

    LoadedSector* load();


protected:
    std::string m_name;
    std::string m_prefix;
    Universe& m_universe;
    LoadedSector* m_loadedSector;
    std::shared_ptr<Sector> m_sector;
};

