#include "oculusmanager.h"

#include <iostream>


HMDManager::HMDManager(Game* game):
    m_game(game),
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

HMDManager::~HMDManager() {
    m_deviceManager->Release();

    if(m_hmd) {
        m_hmd->Release();
    }
}

void HMDManager::setupHMD() {
    m_hmd = hmd;

    m_game->viewer().toStereoMode(m_hmd->stereoRenderInfo());
    m_game->inputHandler().setHMD(m_hmd);
}

HMD* HMDManager::hmd() {
    OVR::HMDDevice* hmd = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

    if (hmd != nullptr) {
        return new HMD(hmd);
    } else {
        return nullptr;
    }
}

