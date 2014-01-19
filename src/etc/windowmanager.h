#pragma once

#include <vector>

#include "geometry/size.h"
#include "geometry/viewport.h"

struct GLFWmonitor;

class WindowManager {
public:
    static WindowManager* instance();

    Size<int> resolution() const;
    Viewport viewport() const;

    float aspectRatio() const;

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

