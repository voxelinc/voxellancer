#pragma once

#include <memory>
#include <string>

#include "textfieldhudgetvoxels.h"

class VoxelFont;
class ButtonHudget;
class VoxelCluster;

class ButtonHudgetVoxels : public TextFieldHudgetVoxels {
public:
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget);
    ButtonHudgetVoxels(ButtonHudget* textFieldHudget, std::string content, glm::vec3 direction, float scale);
    ~ButtonHudgetVoxels();

    void setContent(std::string content);

    //void update(float deltaSec);

    void updateBounds();

    virtual void draw() override;

    //virtual bool isAt(const Ray& ray) const override;

protected:
    VoxelCluster* m_horizontalBounds;
    VoxelCluster* m_verticalBounds;

};

