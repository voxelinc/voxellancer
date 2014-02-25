#include "textfieldhudget.h"

#include "hud.h"
#include "textfieldhudgetvoxels.h"


TextFieldHudget::TextFieldHudget(HUD* hud, int numberOfLetters) :
Hudget(hud)
{

}

TextFieldHudget::~TextFieldHudget() = default;

void TextFieldHudget::update(float deltaSec) {
}

void TextFieldHudget::draw() {
    //m_voxels->draw();
}


