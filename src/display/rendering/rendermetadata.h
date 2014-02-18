#pragma once

#include "display/eyeside.h"


class Camera;

// metadata that is passed to a renderpass
class RenderMetaData {
public:
    RenderMetaData(const Camera& camera, EyeSide eyeside);

    const Camera& camera() const;
    EyeSide eyeside() const;

private:
    const Camera& m_camera;
    EyeSide m_eyeside;
};
