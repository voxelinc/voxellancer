#pragma once

#include <memory>
#include <list>

#include <glow/ref_ptr.h>


class Mission;

class MissionSystem {
public:
    MissionSystem();
    ~MissionSystem();

    void update(float deltaSec);

    void addMission(Mission* mission);
    void removeMission(Mission* mission);


protected:
    std::list<glow::ref_ptr<Mission>> m_missions;
};

