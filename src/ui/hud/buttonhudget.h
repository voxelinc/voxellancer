#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "textfieldhudget.h"

class ButtonHudgetVoxels;
class Callback;

class ButtonHudget : public TextFieldHudget {
public:
    ButtonHudget(HUD* hud, std::string content, glm::vec3 direction);
    ButtonHudget(HUD* hud, std::string content, glm::vec3 direction, float scale);
    virtual ~ButtonHudget();

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clicktype) override;

    virtual void setContent(std::string content);

    void registerCallback(void(HUD::*callbackFunction)(ClickType clickType));

protected:
    void(HUD::*callback)(ClickType clicktype);
    std::string m_content;
    std::unique_ptr<ButtonHudgetVoxels> m_voxels;
    std::unique_ptr<Callback> m_callback;
};

