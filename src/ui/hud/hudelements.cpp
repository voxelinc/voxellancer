#include "hudelements.h"

#include "utils/safenormalize.h"

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "hudget.h"
#include "hudgetanimation.h"
#include "hudgethideanimation.h"
#include "textfieldhudget.h"


HUDElements::HUDElements(HUD& hud):
    m_hud(hud),
    m_targetName(new TextFieldHudget(&m_hud, safeNormalize(glm::vec3(0, -1.1f, -2)), 0.025f, "")),
    m_speedLabel(new TextFieldHudget(&m_hud, safeNormalize(glm::vec3(1.5f, -1.1f, -2)), 0.020f, "")),
    m_missionTitle(new TextFieldHudget(&m_hud, safeNormalize(glm::vec3(0.0f, 1.0f, -2)), 0.020f, "")),
    m_missionTitleHider(new HudgetHideAnimation(*m_missionTitle)),
    m_missionCaption(new TextFieldHudget(&m_hud, safeNormalize(glm::vec3(0.0f, 0.8f, -2)), 0.010f, "")),
    m_missionCaptionHider(new HudgetHideAnimation(*m_missionCaption)),
    m_missionMessage(new TextFieldHudget(&m_hud, safeNormalize(glm::vec3(-0.9f, -0.9f, -2)), 0.010f, "")),
    m_missionMessageHider(new HudgetHideAnimation(*m_missionMessage))
{
    addHudget(m_targetName);
    addHudget(m_speedLabel);
    addHudget(m_missionTitle);
    addHudget(m_missionCaption);
    addHudget(m_missionMessage);

    addAnimation(m_missionTitleHider);
    addAnimation(m_missionCaptionHider);
    addAnimation(m_missionMessageHider);
}

HUD& HUDElements::hud() {
    return m_hud;
}

void HUDElements::addHudget(Hudget* hudget) {
    m_hudgets.push_back(std::unique_ptr<Hudget>(hudget));
}

void HUDElements::removeHudget(Hudget* hudget) {
    m_hudgets.remove_if([&] (std::unique_ptr<Hudget>& hudgetPtr) {
        return hudgetPtr.get() == hudget;
    });
}

std::list<std::unique_ptr<Hudget>>& HUDElements::hudgets() {
    return m_hudgets;
}

void HUDElements::addAnimation(HudgetAnimation* animation) {
    m_animations.push_back(std::unique_ptr<HudgetAnimation>(animation));
}

void HUDElements::setTargetName(const std::string& name) {
    m_targetName->setText(name);
}

void HUDElements::setSpeed(const std::string& speed) {
    m_speedLabel->setText(speed);
}

void HUDElements::showMissionInfo(const std::string& title, const std::string& caption) {
    m_missionTitle->setText(title);
    m_missionTitleHider->hideIn(10);

    m_missionCaption->setText(caption);
    m_missionCaptionHider->hideIn(9.5f);
}

void HUDElements::showMissionMessage(const std::string& message) {
    m_missionMessage->setText(message);
    m_missionMessageHider->hideIn(8);
}

void HUDElements::showMessage(const std::string& message) {
    showMissionMessage(message); // TODO: different box
}

void HUDElements::update(float deltaSec) {
    for (std::unique_ptr<Hudget>& hudget : m_hudgets) {
        hudget->update(deltaSec);
    }

    for (std::unique_ptr<HudgetAnimation>& animation : m_animations) {
        animation->update(deltaSec);
    }
}

void HUDElements::draw() {
    for (std::unique_ptr<Hudget>& hudget : m_hudgets) {
        if (hudget->visible()) {
            hudget->draw();
        }
    }
}

