#pragma once

#include "display/eyeside.h"


class Camera;

// metadata that is passed to a renderpass
class RenderMetaData {
public:
    RenderMetaData(Camera* camera, EyeSide eyeside);

    Camera* camera() const;
    EyeSide eyeside() const;

private:
    Camera* m_camera;
    EyeSide m_eyeside;
};