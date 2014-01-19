#include "windowmanager.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glow/logging.h>
#include <glow/global.h>
#include <glowutils/FileRegistry.h>

#include "geometry/size.h"


WindowManager* WindowManager::s_instance = nullptr;


WindowManager* WindowManager::instance() {
    if(s_instance == nullptr) {
        s_instance = new WindowManager();
    }
    return s_instance;
}

Size<int> WindowManager::resolution() const {
    int width;
    int height;

    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    return Size<int>(width, height);
}

Viewport WindowManager::viewport() const {
    return Viewport(0, 0, resolution().width(), resolution().height());
}

float WindowManager::aspectRatio() const {
    return static_cast<float>(resolution().width()) / static_cast<float>(resolution().height());
}

void WindowManager::setWindowedResolution(const Size<int>& resolution) {
    GLFWwindow* window = glfwCreateWindow(resolution.width(), resolution.height(), "Voxellancer", NULL, NULL);

#ifndef WIN32
    if (window == nullptr) {
        // If 3.1 is not available and this is linux, assume we want mesa software rendering and try again
        putenv("LIBGL_ALWAYS_SOFTWARE=1");

        glfwTerminate();
        if (!glfwInit()) {
            glow::fatal("could not init glfw");
            exit(-1);
        }

        window = glfwCreateWindow(resolution.width(), resolution.height(), "Voxellancer", NULL, NULL);
    }
#endif

    if (window == nullptr) {
        glfwTerminate();
        glow::fatal("Could not create window");
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

void WindowManager::setFullScreenResolution(const Size<int>& resolution, int monitor) {
    GLFWwindow* window = glfwCreateWindow(resolution.width(), resolution.height(), "Voxellancer", monitors()[monitor], NULL);

#ifndef WIN32
    if (window == nullptr) {
        // If 3.1 is not available and this is linux, assume we want mesa software rendering and try again
        putenv("LIBGL_ALWAYS_SOFTWARE=1");

        glfwTerminate();
        if (!glfwInit()) {
            glow::fatal("could not init glfw");
            exit(-1);
        }

        window = glfwCreateWindow(resolution.width(), resolution.height(), "Voxellancer",  monitors()[monitor], NULL);
    }
#endif

    if (window == nullptr) {
        glfwTerminate();
        glow::fatal("Could not create window");
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

bool WindowManager::fullScreen() const {

}

void WindowManager::setFullScreen(bool fullScreen) {

}

std::vector<GLFWmonitor*> WindowManager::monitors() const {
    std::vector<GLFWmonitor*> result;

    int monitorCount;
    GLFWmonitor** vmonitors = glfwGetMonitors(&monitorCount);

    for(int m = 0; m < monitorCount; m++) {
        result.push_back(vmonitors[m]);
    }

    return result;
}

int WindowManager::currentMonitor() const {
    std::vector<GLFWmonitor*> monitors = this->monitors();

    for(int m = 0; m < monitors.size(); m++) {
        GLFWmonitor* monitor = monitors[m];
        if(monitor == glfwGetWindowMonitor(glfwGetCurrentContext())) {
            return m;
        }
    }

    return -1;
}

WindowManager::WindowManager() {

}
