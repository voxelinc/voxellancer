#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "display/scene.h"

#include "property/property.h"


class GamePlay;
class VoxelRenderer;
class SoundManager;
class CameraHead;
class FrameBuffer;
class Blitter;
class RenderPipeline;
class Player;
class Starfield;
class WorldTreeRenderer;

class GamePlayScene: public Scene {
public:
    GamePlayScene(GamePlay& gamePlay);
    virtual ~GamePlayScene();

   virtual void update(float deltaSec) override;

    bool worldTreeRendererEnabled() const;
    void setWorldTreeRendererEnabled(bool enabled);


protected:
    GamePlay& m_gamePlay;

    std::shared_ptr<Starfield> m_starField;

    bool m_worldTreeRendererEnabled;
    std::unique_ptr<WorldTreeRenderer> m_worldTreeRenderer;


    void drawImpl(const Camera& camera) const override;
};

