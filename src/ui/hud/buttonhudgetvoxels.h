#pragma once

#include <memory>
#include <string>

#include "textfieldhudgetvoxels.h"

class VoxelFont;
class ButtonHudget;
class VoxelCluster;

class ButtonHudgetVoxels : public TextFieldHudgetVoxels {
public:
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget, glm::vec3 direction, TextOrientation textOrienation = TextOrientation::BACKWARDS, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7, ButtonStyle buttonStyle = ButtonStyle::BORDERED);
    ~ButtonHudgetVoxels();

    virtual void setText(const std::string& text);

    void updateBounds();

    virtual void draw() override;

    ButtonStyle buttonStyle();
    void setButtonStyle(ButtonStyle buttonStyle);

protected:
    std::unique_ptr<VoxelCluster> m_buttonVoxels;
    Hudget* m_hudget;

    ButtonStyle m_buttonStyle;
};

