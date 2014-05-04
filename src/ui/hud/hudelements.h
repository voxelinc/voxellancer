#pragma once

#include <list>
#include <memory>
#include <string>


class HUD;
class Hudget;
class HudgetAnimation;
class HudgetHideAnimation;
class TextFieldHudget;

/**
 * Class that holds all passive elements of the HUD, such
 * as labels etc., to lift some weight from the main HUD class
 */
class HUDElements {
public:
    HUDElements(HUD& hud);

    HUD& hud();

    void addHudget(Hudget* hudget);
    void removeHudget(Hudget* hudget);
    std::list<std::unique_ptr<Hudget>>& hudgets();

    void addAnimation(HudgetAnimation* animation);

    void setTargetName(const std::string& name);
    void setSpeed(const std::string& speed);

    void showMissionInfo(const std::string& title, const std::string& caption);
    void showMissionMessage(const std::string& message);
    void showMessage(const std::string& message);

    void update(float deltaSec);
    void draw();


protected:
    HUD& m_hud;

    std::list<std::unique_ptr<Hudget>> m_hudgets;
    std::list<std::unique_ptr<HudgetAnimation>> m_animations;

    TextFieldHudget* m_speedLabel;
    TextFieldHudget* m_targetName;

    TextFieldHudget* m_missionTitle;
    HudgetHideAnimation* m_missionTitleHider;

    TextFieldHudget* m_missionCaption;
    HudgetHideAnimation* m_missionCaptionHider;

    TextFieldHudget* m_missionMessage;
    HudgetHideAnimation* m_missionMessageHider;
};

