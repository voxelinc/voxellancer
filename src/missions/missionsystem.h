#pragma once

#include <memory>
#include <unordered_map>


class Mission;

class MissionSystem {
public:
    MissionSystem();
    ~MissionSystem();

    void update(float deltaSec);

    void addMission(std::shared_ptr<Mission> mission);
    void removeMission(Mission* mission);


protected:
    std::unordered_map<Mission*, std::shared_ptr<Mission>> m_missions;
};

