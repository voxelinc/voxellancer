#pragma once

#include <memory>
#include <string>
#include <functional>

#include "hudget.h"
#include "ui/voxelfontconstants.h"

class ButtonHudgetVoxels;
class TextFieldHudgetVoxels;

class ButtonHudget : public Hudget{
public:
    ButtonHudget(HUD* hud, glm::vec3 direction, std::function<void(ClickType clickType)> callback, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7, bool bounds = true);
    virtual ~ButtonHudget();

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clicktype) override;

    virtual void setContent(std::string content);

    void registerCallback(std::function<void(ClickType clickType)> callback);

protected:
    std::function<void(ClickType clickType)> m_callback;
    std::string m_content;
    std::unique_ptr<ButtonHudgetVoxels> m_buttonVoxels;
};

