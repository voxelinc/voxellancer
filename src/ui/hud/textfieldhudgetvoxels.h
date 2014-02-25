#pragma once

#include <memory>
#include <string>

#include "hudget.h"

class VoxelFont;
class TextFieldHudget;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget);

    void setContent(std::string content);

    void update(float deltaSec);
    void draw();

protected:
    TextFieldHudget* m_textFieldHudget;
    std::string m_content;
    VoxelFont* m_voxelFont;
    //std::unique_ptr<TextFieldHudgetVoxels> m_voxels;
};

