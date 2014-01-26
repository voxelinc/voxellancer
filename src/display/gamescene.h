#pragma once

#include <memory>

#include "scene.h"


class Game;
class VoxelRenderer;
class HD3000Dummy;
class SoundManager;
class CameraHead;
class MonoBlitProgram;
class FrameBuffer;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    void setCameraHead(CameraHead* head);

    virtual void draw(Camera* camera, glow::FrameBufferObject* destination, const Viewport& viewPort) override;
    virtual void update(float deltaSec);
    virtual void activate();
    virtual void deactivate();

    void setViewportResolution(const Size<int>& viewportResolution);

protected:
    Game* m_game;
    CameraHead* m_head;
    std::shared_ptr<MonoBlitProgram> m_blitter;
    std::shared_ptr<FrameBuffer> m_colorFbo;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<HD3000Dummy> m_hd3000dummy;
    std::shared_ptr<SoundManager> m_soundManager;
};

