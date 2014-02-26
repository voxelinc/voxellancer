#pragma once

#include <memory>
#include <string>

#include "hudget.h"

class VoxelFont;
class TextFieldHudget;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget);
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, std::string content);

    void setContent(std::string content);

    void update(float deltaSec);
    void draw();

    virtual bool isAt(const Ray& ray) const;

protected:
    TextFieldHudget* m_textFieldHudget;
    std::string m_content;
    VoxelFont* m_voxelFont;
};

