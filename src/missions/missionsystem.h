#pragma once

#include <list>
#include <memory>


class Mission;

class MissionSystem {
public:
    MissionSystem();
    ~MissionSystem();

    void update(float deltaSec);

    void addMission(Mission* mission);
    void removeMission(Mission* mission);


protected:
    std::list<std::unique_ptr<Mission>> m_missions;
};

