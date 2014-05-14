#pragma once

#include <string>
#include <fstream>


class ActionKeyMapping;
class InputMapping;

// This will probably not work if voxellancer is installed!
// We need to switch to a non write-protected folder for configs
class InputConfigWriter {

public:
    InputConfigWriter(const std::string& file);
    ~InputConfigWriter();

    void write(ActionKeyMapping& mapping);

protected:
    std::ofstream m_file;

    void write(const std::string& name, const InputMapping& mapping);
};
