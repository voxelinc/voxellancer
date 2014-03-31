#include "buttonhudget.h"

#include "hud.h"
#include "buttonhudgetvoxels.h"

ButtonHudget::ButtonHudget(HUD* hud, glm::vec3 direction, const std::function<void(ClickType clickType)>& callback, float scale, std::string content, FontSize fontSize, bool bounds) :
    Hudget(hud),
    m_buttonVoxels(new ButtonHudgetVoxels(this, direction, scale, content, fontSize, bounds)),
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

void ButtonHudget::registerCallback(const std::function<void(ClickType clickType)>& callback) {
    m_callback = callback;
}

void ButtonHudget::setContent(std::string content) {
    m_buttonVoxels->setContent(content);
}