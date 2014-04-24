#include "buttonhudget.h"

#include "hud.h"
#include "buttonhudgetvoxels.h"

ButtonHudget::ButtonHudget(HUD* hud, glm::vec3 direction, const std::function<void(ClickType clickType)>& callback, TextOrientation textOrientation, float scale, std::string content, FontSize fontSize, ButtonStyle buttonStyle) :
    Hudget(hud),
    m_buttonVoxels(new ButtonHudgetVoxels(this, direction, textOrientation, scale, content, fontSize, buttonStyle)),
    m_callback(callback)
{
    m_buttonVoxels->updateBounds();
}

ButtonHudget::~ButtonHudget() = default;

void ButtonHudget::update(float deltaSec) {
}

void ButtonHudget::draw() {
    m_buttonVoxels->draw();
}

bool ButtonHudget::isAt(const Ray& ray) const {
    return m_buttonVoxels->isAt(ray);
}

void ButtonHudget::onClick(ClickType clickType) {
    assert(m_callback);
    m_callback(clickType);
}

void ButtonHudget::setCallback(const std::function<void(ClickType clickType)>& callback) {
    m_callback = callback;
}

void ButtonHudget::setText(const std::string& content) {
    m_buttonVoxels->setText(content);
}

void ButtonHudget::setTextOrientation(TextOrientation textOrientation) {
    m_buttonVoxels->setTextOrientation(textOrientation);
}

ButtonStyle ButtonHudget::buttonStyle() {
    return m_buttonVoxels->buttonStyle();
}

void ButtonHudget::setButtonStyle(ButtonStyle buttonStyle) {
    m_buttonVoxels->setButtonStyle(buttonStyle);
}