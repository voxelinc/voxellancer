#include "textfieldhudget.h"

#include "hud.h"
#include "textfieldhudgetvoxels.h"


TextFieldHudget::TextFieldHudget(HUD* hud, const glm::vec3& direction, float scale, const std::string& text, FontSize size) :
    Hudget(hud),
    m_text(text),
    m_voxels(new TextFieldHudgetVoxels(this, direction, scale, text, size))
{
    m_direction = direction;
}

TextFieldHudget::~TextFieldHudget() = default;

void TextFieldHudget::update(float deltaSec) {

}

void TextFieldHudget::draw() {
    m_voxels->draw();
}

void TextFieldHudget::setText(const std::string& text) {
    m_text = text;
    m_voxels->setText(text);
}

void TextFieldHudget::setDirection(const glm::vec3& direction) {
    m_voxels->setDirection(direction);
}

bool TextFieldHudget::isAt(const Ray& ray) const {
    return m_voxels->isAt(ray);
}

void TextFieldHudget::onClick(ClickType clickType) {
    // Nothing to do here
}

