#include "hmdmanager.h"

#include <glow/logging.h>

#include <iostream>

#include "display/viewer.h"

#include "gamestate/game.h"


std::weak_ptr<HMDManager> HMDManager::s_instance;

std::shared_ptr<HMDManager> HMDManager::instance() {
    if (std::shared_ptr<HMDManager> hmdManager = s_instance.lock()) {
        return hmdManager;
    } else {
        hmdManager = std::shared_ptr<HMDManager>(new HMDManager());
        s_instance = hmdManager;
        return hmdManager;
    }
}

HMDManager::~HMDManager() {
    m_deviceManager->Release();
    delete m_hmd;
}

void HMDManager::setupHMD(Viewer& viewer) {
    if(!m_hmd) {
        OVR::HMDDevice* ovrHMD = m_deviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
        if(ovrHMD) {
            m_hmd = new HMD(ovrHMD);
        }
    }

    if(m_hmd) {
        viewer.switchToStereoView(m_hmd->stereoRenderInfo());
    } else {
        glow::warning("Failed to setup HMD. No Oculus Rift connected?");
    }
}

HMD* HMDManager::hmd() {
    return m_hmd;
}

HMDManager::HMDManager():
    m_hmd(nullptr),
    m_deviceManager(nullptr)
{
    m_deviceManager = OVR::DeviceManager::Create();
}

