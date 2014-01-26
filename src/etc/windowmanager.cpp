#include "windowmanager.h"

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

    if (window == nullptr) {
        glfwTerminate();
        glow::fatal("Could not create window");
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

void WindowManager::setFullScreenResolution(int monitorIndex) {
    std::vector<GLFWmonitor*> monitors = this->monitors();
    assert(monitors.size() > 0);

    GLFWwindow* window;
    GLFWmonitor* monitor;

    if(monitorIndex >= monitors.size()) {
        glow::info("Using primary monitors since specified monitor is not available");
        monitor = glfwGetPrimaryMonitor();
    }
    else {
        monitor = monitors[monitorIndex];
    }
    assert(monitor);

    Size<int> resolution = currentResolution(monitor);

    glow::info("Fullscreen resolution %d; x %d;", resolution.width(), resolution.height());

    window = glfwCreateWindow(resolution.width(), resolution.height(), "Voxellancer", monitor, NULL);
    if (window == nullptr) {
        glfwTerminate();
        glow::fatal("Could not create window");
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

void WindowManager::shutdown() {
    glfwDestroyWindow(glfwGetCurrentContext());
}

bool WindowManager::fullScreen() const {
    return false; // TODO
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

Size<int> WindowManager::currentResolution(GLFWmonitor* monitor) {
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    return Size<int>(mode->width, mode->height);
}
