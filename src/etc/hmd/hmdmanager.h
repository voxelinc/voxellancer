#pragma once

#include <OVR.h>

#include "oculus.h"


class HMDManager {
public:
    HMDManager(Game* game);
    ~HMDManager();

    void setupHMD();

    HMD* hmd();


protected:
    Game* m_game;
    HMD* hmd;
    OVR::DeviceManager* m_deviceManager;
};

