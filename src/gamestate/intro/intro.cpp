#include "intro.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "gamestate/game.h"

#include "introscene.h"


Intro::Intro(Game* game):
    GameState("Intro", game),
    m_scene(new IntroScene(*this)),
    m_cameraDolly(new CameraDolly()),
    m_cameraHead(new CameraHead(m_cameraDolly.get()))
{

}

const Scene& Intro::scene() const {
    return *m_scene;
}

const CameraHead& Intro::cameraHead() const {
    return *m_cameraHead;
}

void Intro::update(float deltaSec) {

}

void Intro::onEntered() {

}

void Intro::onLeft() {

}

