#pragma once

#include <memory>
#include <string>
#include <vector>


class Jumpgate;
class JumpgateLoader;
class Sector;
class Universe;

class SectorLoader {
public:
    SectorLoader(const std::string& name, const std::string& prefix, Universe& universe);
    virtual ~SectorLoader();

    std::shared_ptr<Sector> sector();

    Jumpgate* jumpgate(int index);

    void foreachJumpgateLoader(const std::function<void(JumpgateLoader*)> function);


protected:
    std::string m_name;
    std::string m_prefix;
    Universe& m_universe;

    bool m_loaded;

    std::shared_ptr<Sector> m_sector;

    std::vector<std::unique_ptr<JumpgateLoader>> m_jumpgateLoaders;


    void lazyLoad();
    void loadSkybox();
    void loadLight();
    void loadJumpgates();
    void loadJumpgate(int index);
};

