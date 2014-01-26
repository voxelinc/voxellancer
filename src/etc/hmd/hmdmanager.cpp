#include "hmdmanager.h"

#include <glow/logging.h>

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

    if(m_hmd) {
        m_game->viewer().switchToStereoView(m_hmd->stereoRenderInfo());
        m_game->inputHandler().setHMD(m_hmd);
    } else {
        glow::warning("Failed to setup HMD. No Oculus Rift connected?");
    }
}

HMD* HMDManager::hmd() {
    if(m_hmd == nullptr) {
        OVR::HMDDevice* ovrHMD = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
        if(ovrHMD) {
            m_hmd = new HMD(ovrHMD);
        }
    }
    return m_hmd;
}

