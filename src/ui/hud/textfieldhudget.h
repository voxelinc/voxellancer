#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "ui/voxelfontconstants.h"

class TextFieldHudgetVoxels;


class TextFieldHudget : public Hudget {
public:
    TextFieldHudget(HUD* hud, const glm::vec3& direction, TextOrientation textOrientation = TextOrientation::FORWARDS, float scale = 0.5f, const std::string& content = "", FontSize fontSize = FontSize::SIZE5x7);
    virtual ~TextFieldHudget();

    void setText(const std::string& content);
    void setDirection(const glm::vec3& direction);

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clickType) override;


protected:
    std::string m_text;
    std::unique_ptr<TextFieldHudgetVoxels> m_voxels;
};

