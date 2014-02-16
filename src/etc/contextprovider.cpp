#include "contextprovider.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glow/logging.h>
#include <glow/global.h>
#include <glowutils/FileRegistry.h>

#include "geometry/size.h"

#include "property/property.h"


ContextProvider* ContextProvider::s_instance = nullptr;


ContextProvider* ContextProvider::instance() {
    if(s_instance == nullptr) {
        s_instance = new ContextProvider();
    }
    return s_instance;
}

Size<int> ContextProvider::resolution() const {
    int width;
    int height;

    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    return Size<int>(width, height);
}

Viewport ContextProvider::viewport() const {
    return Viewport(0, 0, resolution().width(), resolution().height());
}

float ContextProvider::aspectRatio() const {
    return static_cast<float>(resolution().width()) / static_cast<float>(resolution().height());
}

void ContextProvider::initWindowed(int majorVersionRequire, int minorVersionRequire, const Size<int>* resolution, const Size<int>* position) {
    m_majorVersionRequire = majorVersionRequire;
    m_minorVersionRequire = minorVersionRequire;

    setWindowHints();

    GLFWwindow* window;
    if (resolution) {
        window = glfwCreateWindow(resolution->width(), resolution->height(), "Voxellancer", NULL, NULL);
    } else {
        window = glfwCreateWindow(Property<int>("window.width"), Property<int>("window.height"), "Voxellancer", NULL, NULL);
    }

    if (window == nullptr) {
        glfwTerminate();
        glow::fatal("Could not create window");
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    m_fullScreen = false;
    if (position) {
        glfwSetWindowPos(window, position->width(), position->height());
    }

    for (ContextDependant* dependant : m_contextDependants) {
        dependant->afterContextRebuild();
    }
}

void ContextProvider::initFullScreen(int majorVersionRequire, int minorVersionRequire, int monitorIndex) {
    m_majorVersionRequire = majorVersionRequire;
    m_minorVersionRequire = minorVersionRequire;

    setWindowHints();

    std::vector<GLFWmonitor*> monitors = this->monitors();
    assert(monitors.size() > 0);
    m_lastFullScreenMonitorIndex = monitorIndex;

    GLFWwindow* window;
    GLFWmonitor* monitor;

    if(monitorIndex >= monitors.size()) {
        glow::info("Using primary monitor since specified monitor is not available");
        monitor = glfwGetPrimaryMonitor();
    } else {
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
    m_fullScreen = true;

    for (ContextDependant* dependant : m_contextDependants) {
        dependant->afterContextRebuild();
    }
}

void ContextProvider::shutdown() {
    for (ContextDependant* dependant : m_contextDependants) {
        dependant->beforeContextDestroy();
    }
    glfwDestroyWindow(glfwGetCurrentContext());
}

bool ContextProvider::fullScreen() const {
    return m_fullScreen;
}

void ContextProvider::toggleFullScreen() {
    if (fullScreen()) {
        shutdown();
        if (m_lastWindowedPos.width() == -1) {
            initWindowed(m_majorVersionRequire, m_minorVersionRequire);
        } else {
            initWindowed(m_majorVersionRequire, m_minorVersionRequire, &m_lastWindowedSize, &m_lastWindowedPos);
        }
    } else {
        int x, y;
        glfwGetWindowPos(glfwGetCurrentContext(), &x, &y);
        m_lastWindowedPos.setWidth(x);
        m_lastWindowedPos.setHeight(y);
        glfwGetWindowSize(glfwGetCurrentContext(), &x, &y);
        m_lastWindowedSize.setWidth(x);
        m_lastWindowedSize.setHeight(y);

        shutdown();
        if (m_lastFullScreenMonitorIndex == -1) {
            initFullScreen(m_majorVersionRequire, m_minorVersionRequire);
        } else {
            initFullScreen(m_majorVersionRequire, m_minorVersionRequire, m_lastFullScreenMonitorIndex);
        }
    }
}

std::vector<GLFWmonitor*> ContextProvider::monitors() const {
    std::vector<GLFWmonitor*> result;

    int monitorCount;
    GLFWmonitor** vmonitors = glfwGetMonitors(&monitorCount);

    for(int m = 0; m < monitorCount; m++) {
        result.push_back(vmonitors[m]);
    }

    return result;
}

int ContextProvider::currentMonitor() const {
    std::vector<GLFWmonitor*> monitors = this->monitors();

    for(int m = 0; m < monitors.size(); m++) {
        GLFWmonitor* monitor = monitors[m];
        if(monitor == glfwGetWindowMonitor(glfwGetCurrentContext())) {
            return m;
        }
    }

    return -1;
}


Size<int> ContextProvider::currentResolution(GLFWmonitor* monitor) {
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    return Size<int>(mode->width, mode->height);
}

void ContextProvider::registerContextDependant(ContextDependant* dependant) {
    assert(std::find(m_contextDependants.begin(), m_contextDependants.end(), dependant) == m_contextDependants.end());
    m_contextDependants.insert(dependant);
}

void ContextProvider::unregisterContextDependant(ContextDependant* dependant) {
    m_contextDependants.erase(dependant);
}

ContextProvider::ContextProvider() :
    m_contextDependants(),
    m_fullScreen(false),
    m_majorVersionRequire(0),
    m_minorVersionRequire(0),
    m_lastWindowedPos(-1, -1),
    m_lastWindowedSize(-1, -1),
    m_lastFullScreenMonitorIndex(-1)
{
}

void ContextProvider::setWindowHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_majorVersionRequire);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minorVersionRequire);
#if defined(NDEBUG)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#else
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
}

