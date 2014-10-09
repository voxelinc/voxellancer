#pragma once

#include <memory>
#include <string>
#include <functional>

#include "hudget.h"
#include "ui/voxelfontconstants.h"


class ButtonHudgetVoxels;
class TextFieldHudgetVoxels;

class ButtonHudget : public Hudget {
public:
    ButtonHudget(HUD* hud, const glm::vec3& direction, const std::function<void(ClickType clickType)>& callback, TextOrientation textOrientation = TextOrientation::FORWARDS, float scale = 0.5f, const std::string& content = "", FontSize fontSize = FontSize::SIZE5x7, ButtonStyle borderStyle = ButtonStyle::BORDERED);
    virtual ~ButtonHudget();

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clicktype) override;

    void setText(const std::string& content);

    void setCallback(const std::function<void(ClickType clickType)>& callback);

    void setTextOrientation(TextOrientation textOrientation);

    ButtonStyle buttonStyle();
    void setButtonStyle(ButtonStyle buttonStyle);

protected:
    std::function<void(ClickType clickType)> m_callback;
    std::string m_content;
    std::unique_ptr<ButtonHudgetVoxels> m_buttonVoxels;
};

