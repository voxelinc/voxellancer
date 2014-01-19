#include "commandlineparser.h"

#include <string>


CommandLineParser::CommandLineParser():
    m_hmd(false),
    m_stereoView(false)
{

}

void CommandLineParser::parse(int argc, char* argv[]) {
    for(int a = 1; a < argc; a++) {
        std::string arg(argv[a]);

        if(arg == "-hmd") {
            m_hmd = true;
            m_stereoView = true;
        }

        if(arg == "-stereo") {
            m_stereoView = true;
        }
    }
}

bool CommandLineParser::hmd() const {
    return m_hmd;
}

bool CommandLineParser::stereoView() const {
    return m_stereoView;
}
