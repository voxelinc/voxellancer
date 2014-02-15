#pragma once

#include <unordered_set>
#include <vector>

#include "etc/contextdependant.h"
#include "geometry/size.h"
#include "geometry/viewport.h"

struct GLFWmonitor;

class ContextProvider {
public:
    static ContextProvider* instance();

    Size<int> resolution() const;
    Viewport viewport() const;
    float aspectRatio() const;

    void initWindowed(int majorVersionRequire, int minorVersionRequire, const Size<int>* resolution = nullptr, const Size<int>* position = nullptr);
    void initFullScreen(int majorVersionRequire, int minorVersionRequire, int monitorIndex = 0);

    bool fullScreen() const;
    void toggleFullScreen();

    void shutdown();

    std::vector<GLFWmonitor*> monitors() const;
    int currentMonitor() const;

    void registerContextDependant(ContextDependant* dependant);
    void unregisterContextDependant(ContextDependant* dependant);


protected:
    static ContextProvider* s_instance;
    std::unordered_set<ContextDependant*> m_contextDependants;
    bool m_fullScreen;
    int m_majorVersionRequire;
    int m_minorVersionRequire;
    int m_lastFullScreenMonitorIndex;
    Size<int> m_lastWindowedPos;
    Size<int> m_lastWindowedSize;

    ContextProvider();
    Size<int> currentResolution(GLFWmonitor* monitor);
};

