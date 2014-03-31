#pragma once

#include <memory>
#include <string>

#include "textfieldhudgetvoxels.h"

class VoxelFont;
class ButtonHudget;
class VoxelCluster;

class ButtonHudgetVoxels : public TextFieldHudgetVoxels {
public:
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget, glm::vec3 direction, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7, bool bounds = true);
    ~ButtonHudgetVoxels();

    virtual void setText(const std::string& text);

    void updateBounds();

    virtual void draw() override;

protected:
    std::unique_ptr<VoxelCluster> m_buttonVoxels;
    bool m_bounds;
    Hudget* m_hudget;
};

