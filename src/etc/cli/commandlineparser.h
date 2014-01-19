#pragma once


class CommandLineParser {
public:
    CommandLineParser();

    void parse(int argc, char* argv[]);

    bool hmd() const;
    bool stereoView() const;


private:
    bool m_hmd;
    bool m_stereoView;
};
