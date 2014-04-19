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
    ~GamePlayScene();

    virtual void draw(const Camera& camera, glow::FrameBufferObject* target, const Viewport& destinationViewport, EyeSide side = EyeSide::None) const override;
    virtual void update(float deltaSec) override;

    bool worldTreeRendererEnabled() const;
    void setWorldTreeRendererEnabled(bool enabled);

    void setOutputBuffer(int i);


protected:
    std::unique_ptr<Blitter> m_outputBlitter;
    std::unique_ptr<RenderPipeline> m_renderPipeline;
    mutable std::unique_ptr<FrameBuffer> m_framebuffer;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::shared_ptr<Starfield> m_starField;

    bool m_worldTreeRendererEnabled;
    std::unique_ptr<WorldTreeRenderer> m_worldTreeRenderer;

    GamePlay& m_gamePlay;

    Property<glm::vec3> m_defaultLightDir;
    int m_currentOutputBuffer;


    void drawGame(const Camera& camera, const Viewport& destinationViewport) const;
};

