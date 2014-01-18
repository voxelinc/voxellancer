#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "geometry/size.h"


class WindowManager {
public:
    static WindowManager* instance();

    Size<int> resolution() const;

    void setWindowedResolution(const Size<int>& resolution);
    void setFullScreenResolution(const Size<int>& resolution, int monitor = 0);

    bool fullScreen() const;
    void setFullScreen(bool fullScreen);

    std::vector<GLFWmonitor*> monitors() const;
    int currentMonitor() const;


protected:
    static WindowManager* s_instance;

    WindowManager();
};

