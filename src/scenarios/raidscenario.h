#pragma once

#include "basescenario.h"


class GamePlay;

class RaidScenario : public BaseScenario {
public:
    RaidScenario(GamePlay* gamePlay);


protected:
    void populateWorld() override;
};

