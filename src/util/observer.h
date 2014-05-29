#pragma once


class Observer {
protected:
    friend class Observable;

    virtual void updateObserver() = 0;
};

