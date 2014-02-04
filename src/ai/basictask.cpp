#include "basictask.h"


BasicTask::BasicTask(Ship& ship) :
	m_ship(ship)
{
}

void BasicTask::update(float deltaSec) {

}

bool BasicTask::isInProgress() {
    return true;
}