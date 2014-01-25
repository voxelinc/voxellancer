#pragma once

#include "hudobjectfilterupdate.h"


class HUDObjectFilter {
public:
    HUDObjectFilter(HUD* hud);

    HUDObjectFilterUpdate filterUpdate();


protected:
    HUD* m_hud;
};

