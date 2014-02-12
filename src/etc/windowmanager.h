#pragma once

#include <list>
#include <vector>

#include "etc/contextdependant.h"
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
    void setFullScreenResolution(int monitorIndex = 0);

    void shutdown();

    bool fullScreen() const;
    void setFullScreen(bool fullScreen);

    std::vector<GLFWmonitor*> monitors() const;
    int currentMonitor() const;

    void registerContextDependant(ContextDependant* dependant);
    void unRegisterContextDependant(ContextDependant* dependant);


protected:
    static WindowManager* s_instance;
    std::list<ContextDependant*> m_contextDependants;

    WindowManager();
    Size<int> currentResolution(GLFWmonitor* monitor);
};

