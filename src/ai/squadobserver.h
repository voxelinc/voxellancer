#pragma once

#include "utils/observer/observer.h"


class Ship;
class Squad;

class SquadObserver : public Observer {
public:
    SquadObserver();


protected:
    void onEvent(Event* event);

    void onMemberJoin(Squad* squad, Ship* ship);
    void onMemberLeave(Squad* squad, Ship* ship);
    void onNewLeader(Squad* squad, Ship* leader);
};

