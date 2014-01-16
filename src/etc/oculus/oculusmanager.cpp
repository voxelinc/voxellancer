#include "oculusmanager.h"

#include <iostream>


OculusManager::OculusManager():
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

bool OculusManager::isOculusAvailable() const {

}

Oculus* OculusManager::oculus() {
    OVR::HMDDevice* hmd = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

    if (hmd != nullptr) {
        std::cout << "Oculus Rift detected" << std::endl;
        return new Oculus(hmd);
    } else {
        return nullptr;
    }
}
