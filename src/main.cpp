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
#include <glowutils/File.h>

#include "etc/contextprovider.h"
#include "etc/hmd/hmdmanager.h"
#include "etc/cli/commandlineparser.h"

#include "display/stereorenderinfo.h"
#include "display/viewer.h"

#include "property/propertydirectory.h"

#include "gamestate/gameplay/gameplay.h"
#include "gamestate/gameplay/running/gameplayrunning.h"
#include "gamestate/gameplay/running/gameplayrunninginput.h"
#include "gamestate/game.h"
#include "gamestate/gameplay/gameplayscene.h"

#include "utils/filesystem.h"
#include "world/world.h"


static GLint MajorVersionRequire = 3;
static GLint MinorVersionRequire = 1;

static Game* game;

static void checkGLVersion() {
    glow::info("OpenGL Version Needed %;.%; (%;.%; Found)",
        MajorVersionRequire, MinorVersionRequire,
        glow::version().majorVersion, glow::version().minorVersion);
    glow::info("version %;", glow::versionString());
    glow::info("vendor: %;", glow::vendor());
    glow::info("renderer %;", glow::renderer());
    glow::info("core profile: %;", glow::isCoreProfile() ? "true" : "false");
    glow::info("GLSL version: %;", glow::getString(GL_SHADING_LANGUAGE_VERSION));
    glow::info("GL Versionstring: %;\n", glow::versionString());
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
        game->gamePlay().running().input().resizeEvent(width, height);
        game->viewer().setViewport(Viewport(0, 0, width, height));
    }
}

static void toggleFullScreen();

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if ((key == GLFW_KEY_ENTER && action == GLFW_PRESS) &&
        ((glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) ||
        (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS))) {
        toggleFullScreen();
    }
    if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F4 && action == GLFW_PRESS) {
        game->gamePlay().loadScenario(key - GLFW_KEY_F1);
    }
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        glowutils::File::reloadAll();
    }
    if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {
        PropertyManager::instance()->load("data/config.ini");
    }
    if (key == GLFW_KEY_F9 && action == GLFW_PRESS) {
        World::instance()->print_status();
    }
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
        game->gamePlay().scene().setOutputBuffer(key-GLFW_KEY_1);
    }

	game->gamePlay().running().input().keyCallback(key, scancode, action, mods);
}


static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    game->gamePlay().running().input().mouseButtonCallback(button, action, mods);
}

void setGLFWCallbacks(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, resizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

static void miscSettings() {
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
    std::srand((unsigned int)time(NULL));
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


void toggleFullScreen() {
    ContextProvider::instance()->toggleFullScreen();

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    setGLFWCallbacks(window);

    // not checking version etc again

    Size<int> res = ContextProvider::instance()->resolution();
    resizeCallback(window, res.width(), res.height());
}

int main(int argc, char* argv[]) {
    CommandLineParser clParser;
    clParser.parse(argc, argv);

    PropertyManager::instance()->load("data/config.ini");
    glow::info("Config Directory: %;", FileSystem::userConfigDir());
    std::string controlsConfig = FileSystem::userConfigDir() + "/controls.ini";
    if (!FileSystem::exists(controlsConfig)) {
        FileSystem::copyFile("data/controls.ini.default", controlsConfig);
    }
    PropertyManager::instance()->load(controlsConfig);
    PropertyManager::instance()->load("data/voxels.ini", "voxels");

    if (!glfwInit()) {
        glow::fatal("Could not init GLFW");
        exit(-1);
    }

    glfwSetErrorCallback(errorCallback);

    ContextProvider::instance()->setRequiredGLVersion(MajorVersionRequire, MinorVersionRequire);
    if(clParser.fullScreen()) {
        ContextProvider::instance()->initFullScreen(1);
    } else {
        ContextProvider::instance()->initWindowed();
    }

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    setGLFWCallbacks(window);
    checkGLVersion();
    checkOpenMP();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glow::fatal("glewInit() failed");
    }
    CheckGLError();

    miscSettings();

//#define TRYCATCH

#ifdef TRYCATCH
    try {
#endif
        PropertyDirectory("data/worldobjects").read();
        PropertyDirectory("data/equipment/engines").read();
        PropertyDirectory("data/equipment/weapons").read();
        PropertyDirectory("data/equipment/projectiles").read();

        game = new Game();

        if(clParser.hmd()) {
            game->hmdManager().setupHMD(game->viewer());
        } else {
            if(clParser.stereoView()) {
                game->viewer().switchToStereoView(StereoRenderInfo::dummy());
            }
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //game->inputHandler().resizeEvent(width, height);

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
    ContextProvider::instance()->shutdown();
    glfwTerminate();
    OVR::System::Destroy();

    return 0;
}


