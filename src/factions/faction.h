#pragma once

#include <map>
#include <memory>
#include <string>


class FactionMatrix;
class FactionRelation;

class Faction {
public:
    Faction(FactionMatrix* factionMatrix, const std::string& key, const std::string& printName);

    const std::string& key() const;
    const std::string& printName() const;

    std::shared_ptr<FactionRelation>& relationTo(Faction* faction);
    void setRelation(std::shared_ptr<FactionRelation>& relation);


protected:
    FactionMatrix* m_factionMatrix;

    std::string m_key;
    std::string m_printName;

    std::map<Faction*, std::shared_ptr<FactionRelation>> m_relations;
};

