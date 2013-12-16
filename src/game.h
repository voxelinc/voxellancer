#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/ScreenAlignedQuad.h>
#include <glow/Buffer.h>
#include <glow/glow.h>
#include <glowutils/glowutils.h>
#include <glowutils/File.h>

#include <GLFW/glfw3.h>

#include "ui/inputhandler.h"


class HUD;
class Skybox;
class World;
class InputHandler;
class VoxelRenderer;
class HD3000Dummy;
class LinuxVMDummy;
class Ship;


class Game {

public:
	Game(GLFWwindow *window);
	virtual ~Game();
	void initialize();
	void reloadConfig();

    void update(float delta_sec);
	void draw();

    InputHandler * inputHandler();

private:
    void testFMOD();

private:
	GLFWwindow *m_window;
	InputHandler m_inputHandler;
    Player m_player;
	Camera m_camera;

    World * m_world;

    glow::ref_ptr<glow::FrameBufferObject> m_fboGame;
    glow::ref_ptr<glow::FrameBufferObject> m_fboHud;
    glow::ref_ptr<glow::Texture> m_colorGame;
    glow::ref_ptr<glow::RenderBufferObject> m_depthGame;
    glow::ref_ptr<glow::Texture> m_colorHud;
    glow::ref_ptr<glow::RenderBufferObject> m_depthHud;
    glow::ref_ptr<glow::Buffer> m_buffer;
    glow::ref_ptr<glow::VertexArrayObject> m_vertex;
    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glowutils::ScreenAlignedQuad> m_quad;

    //GLuint m_framebuffer;
    //GLuint m_depth;
    //GLuint m_color;

	std::unique_ptr<Skybox> m_skybox;
	std::unique_ptr<HUD> m_hud;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::unique_ptr<HD3000Dummy> m_hd3000dummy;
	std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;
};

