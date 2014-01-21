#pragma once

#include <memory>

#include "scene.h"

class Game;
class VoxelRenderer;
class HD3000Dummy;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    virtual void draw(Camera* camera) override;

protected:
    Game* m_game;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<HD3000Dummy> m_hd3000dummy;
};

