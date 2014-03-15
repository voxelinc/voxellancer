#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "ui/voxelfontconstants.h"

class TextFieldHudgetVoxels;


class TextFieldHudget : public Hudget {
public:
    TextFieldHudget(HUD* hud, glm::vec3 direction, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7);
    virtual ~TextFieldHudget();

    void setContent(std::string content);

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clickType) override;

protected:
    std::string m_content;
    std::unique_ptr<TextFieldHudgetVoxels> m_voxels;
};

