#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "scene.h"
#include "property/property.h"


class Game;
class VoxelRenderer;
class SoundManager;
class CameraHead;
class MonoBlitProgram;
class FrameBuffer;
class Blitter;
class RenderPipeline;
class Player;

class GameScene: public Scene {
public:
    GameScene(Game& game, Player& player);
    virtual ~GameScene();

    void setPlayer(Player* player);

    virtual void draw(Camera& camera, glow::FrameBufferObject* target, EyeSide side = EyeSide::Left) override;
    virtual void update(float deltaSec) override;
    virtual void activate() override;
    virtual void deactivate() override;

    void setOutputBuffer(int i);


protected:
    std::unique_ptr<Blitter> m_blitter;
    std::unique_ptr<RenderPipeline> m_renderPipeline;
    std::unique_ptr<FrameBuffer> m_framebuffer;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<SoundManager> m_soundManager;
    Game* m_game;
    CameraHead* m_head;
    Player* m_player;

    Property<glm::vec3> m_defaultLightDir;
    int m_currentOutputBuffer;
    void drawGame(Camera& camera);
};

