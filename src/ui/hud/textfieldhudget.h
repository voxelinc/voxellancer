#pragma once

#include <memory>
#include <string>

#include "hudget.h"

class TextFieldHudgetVoxels;


class TextFieldHudget : public Hudget {
public:
    TextFieldHudget(HUD* hud, std::string content, glm::vec3 direction);
    virtual ~TextFieldHudget();

    void setContent(std::string content);

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(int button) override;

protected:
    std::string m_content;
    std::unique_ptr<TextFieldHudgetVoxels> m_voxels;
};
