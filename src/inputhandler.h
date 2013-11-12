#pragma once

#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "camera.h"

#include "property/propertymanager.h"
#include "property/property.h"

#include "voxel/voxelcluster.h"


class InputHandler {
public:
	InputHandler(GLFWwindow *window, Camera *camera, VoxelCluster *voxelcluster);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void update(float delta_sec);
	void toggleControls();

protected:
	GLFWwindow *m_window;
	Camera* m_camera;
	VoxelCluster *m_voxelcluster;

	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_fpsControls;

	Property<float> m_angle_translate;
	Property<float> m_move_translate;
};
