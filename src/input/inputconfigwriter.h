#pragma once

#include <string>
#include <fstream>


class ActionKeyMapping;
class InputMapping;

class InputConfigWriter {
public:
    InputConfigWriter(const std::string& file);
    ~InputConfigWriter();

    void write(ActionKeyMapping& mapping);


protected:
    std::ofstream m_file;

    void write(const std::string& name, const InputMapping& mapping);
};

