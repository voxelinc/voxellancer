#pragma once

#include <string>

#include "basescenario.h"


class GamePlay;
class Mission;

class MissionScenario : public BaseScenario {
public:
    MissionScenario(GamePlay* gamePlay, const std::string& path);


protected:
    Mission* m_mission;

    virtual void populateWorld() override;
};

