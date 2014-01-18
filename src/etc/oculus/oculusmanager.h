#pragma once

#include <OVR.h>

#include "oculus.h"


class OculusManager {
public:
    OculusManager();
    ~OculusManager();

    bool isOculusAvailable() const;

    Oculus* oculus();


protected:
    OVR::DeviceManager* m_deviceManager;
};

