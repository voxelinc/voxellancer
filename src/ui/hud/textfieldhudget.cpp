#include "textfieldhudget.h"

#include "hud.h"
#include "textfieldhudgetvoxels.h"


TextFieldHudget::TextFieldHudget(HUD* hud, std::string content, glm::vec3 direction) :
Hudget(hud),
m_content(content),
m_voxels(new TextFieldHudgetVoxels(this, content, direction, 0.04f)) {
    m_direction = direction;
}

TextFieldHudget::TextFieldHudget(HUD* hud, std::string content, glm::vec3 direction, float scale) :
Hudget(hud),
m_content(content),
m_voxels(new TextFieldHudgetVoxels(this, content, direction, scale)) {
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