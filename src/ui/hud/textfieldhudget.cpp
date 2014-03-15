#include "textfieldhudget.h"

#include "hud.h"
#include "textfieldhudgetvoxels.h"

TextFieldHudget::TextFieldHudget(HUD* hud, glm::vec3 direction, float scale, std::string content, FontSize size) :
Hudget(hud),
m_content(content),
m_voxels(new TextFieldHudgetVoxels(this, direction, scale, content, size)) {
    m_direction = direction;
}

TextFieldHudget::~TextFieldHudget() = default;

void TextFieldHudget::update(float deltaSec) {
}

void TextFieldHudget::draw() {
    m_voxels->draw();
}

void TextFieldHudget::setContent(std::string content) {
    m_content = content;
    m_voxels->setContent(content);
}


bool TextFieldHudget::isAt(const Ray& ray) const {
    return m_voxels->isAt(ray);
}

void TextFieldHudget::onClick(ClickType clickType) {
    // Nothing to do here
}