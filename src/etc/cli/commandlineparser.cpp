#include "commandlineparser.h"

#include <string>


CommandLineParser::CommandLineParser():
    m_hmd(false),
    m_stereoView(false)
{

}

void CommandLineParser::parse(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

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
