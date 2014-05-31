#pragma once

#include <memory>
#include <string>


class Sector;
class Universe;

class SectorLoader {
public:
    SectorLoader(const std::string& name, const std::string& prefix, Universe& universe);
    virtual ~SectorLoader();

    std::shared_ptr<Sector>& load();


protected:
    std::string m_name;
    std::string m_prefix;
    Universe& m_universe;
    std::shared_ptr<Sector> m_sector;
};

