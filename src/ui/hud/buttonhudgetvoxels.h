#pragma once

#include <memory>
#include <string>

#include "textfieldhudgetvoxels.h"
#include "hudget.h"

class VoxelFont;
class ButtonHudget;

class ButtonHudgetVoxels : public TextFieldHudgetVoxels {
public:
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget);
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget, std::string content, glm::vec3 direction, float scale);

    void setContent(std::string content);

    void update(float deltaSec);
    ;

    virtual bool isAt(const Ray& ray) const override;


protected:
};

