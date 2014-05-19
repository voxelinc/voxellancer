#pragma once

#include <map>
#include <memory>
#include <string>


class FactionMatrix;
class FactionRelation;
class Universe;

class Faction {
public:
    Faction(FactionMatrix& matrix, const std::string& key, const std::string& printName);

    const std::string& key() const;
    void setPrintName(const std::string& printName);
    const std::string& printName() const;

    FactionRelation& relationTo(Faction& other);

protected:
    FactionMatrix& m_matrix;

    std::string m_key;
    std::string m_printName;
};

