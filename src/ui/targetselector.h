#pragma once

#include <functional>


class WorldObject;
class Player;

class TargetSelector {
public:
    TargetSelector(Player *player);

    void selectNextTarget();
    void selectPreviousTarget();

    void selectTargetOnClick();
    
private:
    Player* m_player;

    template<typename IteratorType>
    WorldObject* findNextTarget(IteratorType begin, IteratorType end);

    std::function<bool(WorldObject*)> canLockOnPredicate();
};
