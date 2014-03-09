#pragma once

#include "faction.h"


class FactionMatrix;

class PlayerFaction : public Faction {
public:
    PlayerFaction(FactionMatrix* factionMatrix);
};

