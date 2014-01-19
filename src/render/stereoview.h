#pragma once

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>

#include "view.h"
#include "stereovieweye.h"


class StereoView: public View {
public:
    StereoView();

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    glow::FrameBufferObject m_fbo;
};

