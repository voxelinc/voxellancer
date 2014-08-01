#include "commandlineparser.h"

#include <string>
#include <glow/logging.h>


CommandLineParser::CommandLineParser():
    m_options()
{

}

void CommandLineParser::parse(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        if (arg[0] == '-') {
            std::string arg(argv[i]+1);
            if (i + 1 < argc) {
                m_options[arg] = argv[i + 1];
            } else {
                m_options[arg] == "";
            }
        }
    }
    checkHelp();
}

bool CommandLineParser::hmd() const {
    return isSet("hmd");
}

bool CommandLineParser::stereoView() const {
    return hmd() || isSet("stereo");
}

bool CommandLineParser::fullScreen() const {
    return hmd() || isSet("fullscreen");
}

bool CommandLineParser::showIntro() const {
    return !isSet("nointro");
}

bool CommandLineParser::isSet(const std::string& arg) const {
    return m_options.count(arg) > 0;
}

void CommandLineParser::checkHelp() {
    if (isSet("help") || isSet("-help") || isSet("h")) {
        glow::debug("Usage: voxellancer [-fullscreen] [-stereo] [-hmd]\n");
        glow::debug("  -fullscreen  fullscreen mode");
        glow::debug("  -stereo      stereo rendering");
        glow::debug("  -hmd         use head mounted display (e.g. OculusRift)");
        glow::debug("  -nointro     [dev] don't show the intro");
        glow::debug("               automatically activates fullscreen and stereo");
        exit(0);
    }
}
