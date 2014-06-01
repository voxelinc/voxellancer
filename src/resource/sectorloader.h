#pragma once

#include <memory>
#include <string>
#include <vector>


class Sector;
class Universe;
class JumpgateLoader;

class SectorLoader {
public:
    SectorLoader(const std::string& name, const std::string& prefix, Universe& universe);
    virtual ~SectorLoader();

    std::shared_ptr<Sector> sector();

    void foreachJumpgateLoader(const std::function<void(JumpgateLoader*)> function);


protected:
    std::string m_name;
    std::string m_prefix;
    Universe& m_universe;

    bool m_loaded;

    std::shared_ptr<Sector> m_sector;

    std::vector<std::unique_ptr<JumpgateLoader>> m_jumpgateLoaders;


    void lazyLoad();
};

