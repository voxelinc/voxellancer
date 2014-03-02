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

    void setRequiredGLVersion(int majorVersionRequire, int minorVersionRequire);

    void initWindowed();
    void initWindowed(const Size<int>& resolution);
    void initWindowed(const Size<int>& resolution, const Size<int>& position);
    void initFullScreen(int monitorIndex = 0);

    void toggleFullScreen();
    void shutdown();

    bool fullScreen() const;
    Size<int> resolution() const;
    Viewport viewport() const;
    float aspectRatio() const;

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
    void setWindowHints();
};

