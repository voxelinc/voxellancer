#include "oculusmanager.h"

#include <iostream>


OculusManager::OculusManager():
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

OculusManager::~OculusManager() {
    m_deviceManager->Release();
}

bool OculusManager::isOculusAvailable() const {
    return false;
}

Oculus* OculusManager::oculus() {
    OVR::HMDDevice* hmd = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

    if (hmd != nullptr) {
        return new Oculus(hmd);
    } else {
        return nullptr;
    }
}

