#include "hmdmanager.h"

#include <iostream>

#include "game.h"


HMDManager::HMDManager(Game* game):
    m_game(game),
    m_hmd(nullptr),
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

HMDManager::~HMDManager() {
    m_deviceManager->Release();
    delete m_hmd;
}

void HMDManager::setupHMD() {
    m_hmd = hmd();

    m_game->viewer().toStereoView(m_hmd->stereoRenderInfo());
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

