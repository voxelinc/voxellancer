#pragma once

#include "geometry/viewport.h"


class CameraHead;
class Scene;
class View;
class StereoRenderInfo;

class Viewer {
public:
    Viewer(const Viewport& viewport);

    void setScene(Scene* scene);
    void setCameraHead(CameraHead* cameraHead);
    void setViewport(const Viewport& viewport);

    void toMonoView();
    void toStereoView(const StereoRenderInfo& stereoRenderInfo);


    void draw();


protected:
    Scene* m_scene;
    View* m_view;
    CameraHead* m_cameraHead;
    Viewport m_viewport;
};

