#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "scene.h"


class Game;
class VoxelRenderer;
class HD3000Dummy;
class SoundManager;
class CameraHead;
class MonoBlitProgram;
class FrameBuffer;
class Blitter;
class RenderPipeline;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    void setCameraHead(CameraHead* head);

    virtual void draw(Camera* camera, glow::FrameBufferObject* destination, const glm::ivec2& resolution) override;

    void drawGame(Camera* camera);

    virtual void update(float deltaSec);
    virtual void activate();
    virtual void deactivate();

    void setOutputBuffer(int i);
protected:
    Game* m_game;
    CameraHead* m_head;
    std::shared_ptr<Blitter> m_blitter;
    std::shared_ptr<FrameBuffer> m_framebuffer;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<HD3000Dummy> m_hd3000dummy;
    std::shared_ptr<SoundManager> m_soundManager;
    std::shared_ptr<RenderPipeline> m_renderPipeline;

    int m_currentOutputBuffer;
};

