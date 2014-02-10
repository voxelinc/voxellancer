#include <iostream>
#include <omp.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <OVR.h>

#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif

#include <GLFW/glfw3.h>

#include <glow/Version.h>
#include <glow/global.h>
#include <glow/logging.h>
#include <glow/debugmessageoutput.h>
#include <glowutils/global.h>
#include <glowutils/FileRegistry.h>

#include "etc/windowmanager.h"
#include "etc/cli/commandlineparser.h"

#include "geometry/viewport.h"

#include "display/stereorenderinfo.h"

#include "ui/inputhandler.h"

#include "game.h"


static GLint MajorVersionRequire = 3;
static GLint MinorVersionRequire = 1;

static Game* game;

static void checkVersion() {
    glow::info("OpenGL Version Needed %;.%; (%;.%; Found)",
        MajorVersionRequire, MinorVersionRequire,
        glow::Version::currentMajorVersion(), glow::Version::currentMinorVersion());
    glow::info("version %;", glow::Version::current().toString());
    glow::info("vendor: %;", glow::Version::vendor());
    glow::info("renderer %;", glow::Version::renderer());
    glow::info("core profile: %;", glow::Version::currentVersionIsInCoreProfile() ? "true" : "false");
    glow::info("GLSL version: %;", glow::getString(GL_SHADING_LANGUAGE_VERSION));
    glow::info("GL Versionstring: %;\n", glow::Version::versionString());
}

static void checkOpenMP() {
    //omp_set_num_threads(4);
#pragma omp parallel
    {
#pragma omp master
        glow::debug("OpenMP with %; threads ", omp_get_num_threads());
    }
}

static void errorCallback(int error, const char* description) {
    glow::warning(description);
}

static void resizeCallback(GLFWwindow* window, int width, int height) {
    glow::info("Resizing viewport to %;x%;", width, height);
    if (width > 0 && height > 0) {
        glViewport(0, 0, width, height);
        game->inputHandler().resizeEvent(width, height);
        game->viewer().setViewport(Viewport(0, 0, width, height));
    }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        glowutils::FileRegistry::instance().reloadAll();
    }
    if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {
        PropertyManager::instance()->load("data/config.ini");
    }
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
        game->setOutputBuffer(key-GLFW_KEY_1);
    }

	game->inputHandler().keyCallback(key, scancode, action, mods);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    game->inputHandler().mouseButtonCallback(button, action, mods);
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y) {

}

void setCallbacks(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, resizeCallback);
}

static void mainloop() {
    glow::debug("Entering mainloop");
    double time = glfwGetTime();
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        double delta = glfwGetTime() - time;
        time += delta;

        game->update(static_cast<float>(delta));
        game->draw();

        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
}


int main(int argc, char* argv[]) {
    CommandLineParser clParser;
    clParser.parse(argc, argv);

    PropertyManager::instance()->load("data/config.ini");

    if (!glfwInit()) {
        glow::fatal("Could not init glfw");
        exit(-1);
    }

    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MajorVersionRequire);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinorVersionRequire);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#if defined(NDEBUG)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#else
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    if(clParser.fullScreen()) {
        WindowManager::instance()->setFullScreenResolution(1);
    } else {
        WindowManager::instance()->setWindowedResolution(Size<int>(Property<int>("window.width"), Property<int>("window.height")));
    }

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    setCallbacks(window);

    checkVersion();
    checkOpenMP();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glow::fatal("glewInit() failed");
    }
    CheckGLError();

    OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

#ifdef WIN32 // TODO: find a way to correctly detect debug extension in linux
    glow::debugmessageoutput::enable();
#endif

#ifdef WIN32
    wglSwapIntervalEXT(1); // glfw doesn't work!?
#else
    glfwSwapInterval(1);
#endif

//#define TRYCATCH

#ifdef TRYCATCH
    try {
#endif
        std::srand((unsigned int)time(NULL));

        game = new Game();

        if(clParser.hmd()) {
            game->hmdManager().setupHMD();
        } else {
            if(clParser.stereoView()) {
                game->viewer().switchToStereoView(StereoRenderInfo::dummy());
            }
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        game->inputHandler().resizeEvent(width, height);

        mainloop();

#ifdef TRYCATCH
    }
    catch (std::exception &e) {
        glfwDestroyWindow(window);
        glfwTerminate();
        glow::fatal("Termination after Exception: %;", e.what());
        std::cout << "Hit enter to quit" << std::endl;
        std::cin.ignore(1, '\n');
    }
#endif

    delete game;
    WindowManager::instance()->shutdown();
    glfwTerminate();
    OVR::System::Destroy();

    return 0;
}


