#include "propertymanager.h"

#include <string>
#include <fstream>

#include <glow/logging.h>

#include "utils/stringhelper.h"

#include "propertycollection.h"
#include "propertyconverter.h"
#include "propertyregex.h"

#include "input/inputmapping.h"


PropertyManager::PropertyManager() {
    addPropertyCollection(new PropertyCollection<float>(float_regex(), PropertyConverter::floatConverter));
    addPropertyCollection(new PropertyCollection<int>(int_regex(), [](std::string s) { return std::stoi(s, nullptr, 0); })); // base=0 allows adding 0x to parse hex
    addPropertyCollection(new PropertyCollection<uint32_t>(uint32_regex(), [](std::string s) { return std::stoul(s, nullptr, 0); })); // base=0 allows adding 0x to parse hex
    addPropertyCollection(new PropertyCollection<char>(char_regex(), [](std::string s) { return s[0]; }));
    addPropertyCollection(new PropertyCollection<bool>(bool_regex(), [](std::string s) { return s == "true" ? true : false; }));
    addPropertyCollection(new PropertyCollection<std::string>(string_regex(), [](std::string s) { return s; }));
    addPropertyCollection(new PropertyCollection<glm::vec2>(vec2_regex(), PropertyConverter::vec2Converter));
    addPropertyCollection(new PropertyCollection<glm::vec3>(vec3_regex(), PropertyConverter::vec3Converter));
    addPropertyCollection(new PropertyCollection<glm::vec4>(vec4_regex(), PropertyConverter::vec4Converter));
    addPropertyCollection(new PropertyCollection<InputMapping>(input_mapping_regex(), PropertyConverter::inputMappingConverter));
    addPropertyCollection(new PropertyCollection<std::list<std::string>>(list_regex(), PropertyConverter::listConverter));
}

PropertyManager::~PropertyManager() = default;

void PropertyManager::load(const std::string& file, const std::string& prefix) {
    std::ifstream input(file);
    std::string line;
    std::string title;

    if (!input.is_open()) {
        glow::fatal("PropertyManager: could not open %;", file);
        throw std::runtime_error("Critical configuration file not readable");
    }

    std::string keyPrefix = prefix.empty() ? "" : prefix + ".";

    while (std::getline(input, line)) {
        regexns::smatch matches;

        bool isTitle = regexns::regex_match(line, matches, title_regex());
        if (isTitle) {
            title = matches[1];
            continue;
        }

        bool isLine = regexns::regex_match(line, matches, line_regex());
        if (isLine) {
            std::string key, key_temp, value;
            key_temp = matches[1];
            key = keyPrefix + title + '.' + key_temp;
            value = matches[2];
            bool success = false;


            for (auto& pair: m_propertyCollections) {
                if (pair.second->update(key, value)) {
                    success = true;
                }
            }

            if (!success) {
                glow::warning("PropertyManager: no match %;: %; (line: %;)", key, value, line);
            } else {
                std::string group = key.substr(0, key.rfind("."));
                std::cout << "Group: " << prefix << " " << group << std::endl;
                std::vector<std::string> path = StringHelper(group).split('.');
                m_rootNode.insert(path);
            }
        }
    }

    changed();
}

PropertyManager * PropertyManager::instance() {
    if (s_instance == nullptr) {
        s_instance = new PropertyManager();
    }
    return s_instance;
}


void PropertyManager::reset() {
    if (s_instance != nullptr) {
        delete s_instance;
        s_instance = nullptr;
    }
}

std::vector<std::string> PropertyManager::groups(const std::string& prefix) const {
    const PropertyNode* node = m_rootNode.find(StringHelper(prefix).split('.'));

    if (!node) {
        glow::debug() << "No such propertypath '" << prefix << "'";
        return std::vector<std::string>();
    } else {
        return node->childrenNames();
    }
}

PropertyManager* PropertyManager::s_instance;

