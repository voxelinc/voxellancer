#pragma once

#include <OVR.h>

#include "hmd.h"


class Game;

class HMDManager {
public:
    HMDManager(Game* game);
    ~HMDManager();

    void setupHMD();

    HMD* hmd();


protected:
    Game* m_game;
    HMD* m_hmd;
    OVR::DeviceManager* m_deviceManager;
};

