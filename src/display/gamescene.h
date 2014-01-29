#pragma once

#include <memory>

#include "utils/hd3000dummy.h"

#include "scene.h"


class Game;
class VoxelRenderer;
class SoundManager;
class Player;

class GameScene: public Scene {
public:
    GameScene(Game* game);

    void setPlayer(Player* player);

    virtual void draw(Camera* camera) override;
    virtual void update(float deltaSec);
    virtual void activate();
    virtual void deactivate();

protected:
    Game* m_game;
    Player* m_player;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<SoundManager> m_soundManager;
    HD3000Dummy m_hd3000dummy;
};

