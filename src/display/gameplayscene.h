#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "scene.h"


class GamePlay;
class VoxelRenderer;
class HD3000Dummy;
class SoundManager;
class CameraHead;
class MonoBlitProgram;
class FrameBuffer;
class Blitter;
class RenderPipeline;
class Player;

class GamePlayScene: public Scene {
public:
    GamePlayScene(GamePlay* inGame, Player* player);
    ~GamePlayScene();

    void setPlayer(Player* player);

    virtual void draw(const Camera& camera, glow::FrameBufferObject* target, EyeSide side = EyeSide::Left) const override;
    virtual void update(float deltaSec) override;

    void setOutputBuffer(int i);


protected:
    std::unique_ptr<Blitter> m_blitter;
    std::unique_ptr<RenderPipeline> m_renderPipeline;
    std::unique_ptr<FrameBuffer> m_framebuffer;
    std::unique_ptr<HD3000Dummy> m_hd3000dummy;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    GamePlay* m_inGame;
    CameraHead* m_head;
    Player* m_player;

    int m_currentOutputBuffer;

    void drawGame(const Camera& camera) const;
};

