#pragma once

#include "scene.h"


class Game;
class VoxelRenderer;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    virtual void draw(Camera* camera) override;


protected:
    Game* m_game;
    VoxelRenderer* m_voxelRenderer;
	HD3000Dummy m_hd3000dummy;
}

