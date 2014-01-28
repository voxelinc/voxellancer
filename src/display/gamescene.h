#pragma once

#include <memory>

#include "scene.h"

class Game;
class VoxelRenderer;
class HD3000Dummy;
class SoundManager;
class CameraHead;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    void setCameraHead(CameraHead* head);

    virtual void draw(Camera* camera) override;
    virtual void update(float deltaSec);
    virtual void activate();
    virtual void deactivate();

protected:
    Game* m_game;
    CameraHead* m_head;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<HD3000Dummy> m_hd3000dummy;
    std::shared_ptr<SoundManager> m_soundManager;
};

