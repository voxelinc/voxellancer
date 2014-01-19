#pragma once

#include <OVR.h>

#include "oculus.h"


class HMDManager {
public:
    HMDManager();
    ~HMDManager();

    bool isOculusAvailable() const;

    HMD* oculus();


protected:
    OVR::DeviceManager* m_deviceManager;
};

