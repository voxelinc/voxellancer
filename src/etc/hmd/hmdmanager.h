#pragma once

#include <memory>


namespace OVR {
    class DeviceManager;
}

class Viewer;
class HMD;

class HMDManager {
public:
    static std::shared_ptr<HMDManager> instance();

    ~HMDManager();

    void setupHMD(Viewer& viewer);

    HMD* hmd();


protected:
    static std::weak_ptr<HMDManager> s_instance;

    HMD* m_hmd;
    OVR::DeviceManager* m_deviceManager;


    HMDManager();
};

