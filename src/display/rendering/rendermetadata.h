#pragma once

#include "display/eyeside.h"


class Camera;

// metadata that is passed to a renderpass
struct RenderMetaData {
    Camera* camera;
    EyeSide eyeside;
};