#pragma once

#include <memory>

#include <OVR.h>

#include "hmd.h"


class Viewer;

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

