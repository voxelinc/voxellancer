#pragma once

namespace OVR {
    class DeviceManager;
}

class Game;
class HMD;

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

