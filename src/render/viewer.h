#pragma once


class CameraHead;
class Scene;
class View;
class StereoRenderInfo;

class Viewer {
public:
    Viewer();

    void setScene(Scene* scene);

    void setCameraHead(CameraHead* cameraHead);

    void toMonoView();
    void toStereoView(const StereoRenderInfo& stereoRenderInfo);

    void resize();

    void draw();


protected:
    Scene* m_scene;
    View* m_view;
    CameraHead* m_cameraHead;
};

