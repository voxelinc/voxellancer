#pragma once


class LoadedSector {
public:
    LoadedSector(std::shared_ptr<Sector>& sector);
    virtual ~LoadedSector();

    void addJumpgate(LoadedJumpgate& jumpgate);

    glow::ref_ptr<Jumpgate> jumpgate(int index);
    const std::vector<std::unique_ptr<LoadedJumpgate>>& loadedJumpgates();


protected:
    std::shared_ptr<Sector> m_sector;
    std::vector<std::unique_ptr<LoadedJumpgate>> m_loadedJumpgates;
};
