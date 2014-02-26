#include "textfieldhudget.h"

#include "hud.h"
#include "textfieldhudgetvoxels.h"


TextFieldHudget::TextFieldHudget(HUD* hud, int numberOfLetters) :
Hudget(hud),
m_voxels(new TextFieldHudgetVoxels(this))
{
    
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