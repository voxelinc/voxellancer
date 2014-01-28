#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "targetguidearrowvoxels.h"


class TargetGuide;

class TargetGuideArrow: public Hudget {
public:
    TargetGuideArrow(TargetGuide* targetGuide);

    void setTargetOrientation(const glm::quat& targetOrientation);
    void setRelativeOrientation(const glm::quat& relativeOrientation);

    virtual glm::vec3 position() const override;
    virtual glm::quat orientation() const override;

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    TargetGuide* m_targetGuide;
    TargetGuideArrowVoxels m_voxels;
    glm::quat m_targetOrientation;
    glm::quat m_relativeOrientation;
};

