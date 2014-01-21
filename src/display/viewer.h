#pragma once

#include "geometry/viewport.h"


class CameraHead;
class Scene;
class View;
class StereoRenderInfo;

class Viewer {
public:
    Viewer(const Viewport& viewport);

    Scene* scene();
    void setScene(Scene* scene);
    void setCameraHead(CameraHead* cameraHead);
    void setViewport(const Viewport& viewport);

    void switchToMonoView();
    void switchToStereoView(const StereoRenderInfo& stereoRenderInfo);
    
    void draw();
    void update(float deltaSec);

protected:
    Scene* m_scene;
    View* m_view;
    CameraHead* m_cameraHead;
    Viewport m_viewport;
};

