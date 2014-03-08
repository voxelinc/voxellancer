#include "buttonhudget.h"

#include "hud.h"
#include "buttonhudgetvoxels.h"
#include "callback.h"

ButtonHudget::ButtonHudget(HUD* hud, std::string content, glm::vec3 direction) :
TextFieldHudget(hud,content,direction),
m_voxels(new ButtonHudgetVoxels(this, content, direction, 0.04f)) {
}

ButtonHudget::ButtonHudget(HUD* hud, std::string content, glm::vec3 direction, float scale) :
TextFieldHudget(hud, content, direction, scale),
m_voxels(new ButtonHudgetVoxels(this, content, direction, scale)) {
}

ButtonHudget::~ButtonHudget() = default;

void ButtonHudget::update(float deltaSec) {
}

void ButtonHudget::draw() {
    m_voxels->draw();
}

bool ButtonHudget::isAt(const Ray& ray) const {
    return m_voxels->isAt(ray);
}

void ButtonHudget::onClick(ClickType clickType) {
    (m_hud->*callback)(clickType);
}

void ButtonHudget::registerCallback(void(HUD::*callbackFunction)(ClickType clickType)) {
    (m_hud->*callbackFunction)(ClickType::Selection);
    //callback = callbackFunction;
}

void ButtonHudget::setContent(std::string content) {
    m_voxels->setContent(content);
}