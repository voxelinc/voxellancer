#pragma once


class BoardComputer;
class WorldObject;

class AiTask {
public:
    AiTask(BoardComputer* boardComputer);

    BoardComputer* boardComputer();

    virtual void update(float deltaSec);
    virtual bool isInProgress();


protected:
    BoardComputer* m_boardComputer;
};

