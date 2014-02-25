#pragma once

#include <memory>
#include <string>

#include "hudget.h"

class VoxelFont;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels();

    void setContent(std::string content);

    void update(float deltaSec);
    void draw();

protected:
    std::string m_content;
    std::unique_ptr<VoxelFont> m_voxelFont;
    //std::unique_ptr<TextFieldHudgetVoxels> m_voxels;
};

