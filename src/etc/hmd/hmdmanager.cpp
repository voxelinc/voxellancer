#include "oculusmanager.h"

#include <iostream>


HMDManager::HMDManager():
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

HMDManager::~HMDManager() {
    m_deviceManager->Release();
}

bool HMDManager::isOculusAvailable() const {
    return false;
}

HMD* HMDManager::oculus() {
    OVR::HMDDevice* hmd = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

    if (hmd != nullptr) {
        return new HMD(hmd);
    } else {
        return nullptr;
    }
}

