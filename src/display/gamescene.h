#pragma once

#include <memory>

#include "utils/hd3000dummy.h"

#include "scene.h"


class Game;
class VoxelRenderer;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    virtual void draw(Camera* camera) override;


protected:
    Game* m_game;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    HD3000Dummy m_hd3000dummy;
};

