#pragma once

#include <memory>

#include "scripting/scriptable.h"


class Squad;
class AiTask;
class Ship;

class AiGroupTask : public Scriptable {
public:
    AiGroupTask(Squad& squad);

    virtual void update(float deltaSec);
    virtual bool isInProgress();

protected:
    friend class Squad;
    // interface for Squad
    virtual void onMemberJoin(Ship* member);
    virtual void onMemberLeave(Ship* member);
    virtual void onNewLeader(Ship* leader);

    void setLeaderTask(std::shared_ptr<AiTask> task);
    void setMembersToFollowLeader();

    Squad& m_squad;
};

