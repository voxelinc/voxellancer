#include "intro.h"

#include <vector>

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "gamestate/game.h"

#include "utils/statemachine/trigger.h"

#include "introscene.h"


namespace {
    const std::vector<std::string> INTRO_LINES({
       "This game is still in its",
       "earlier days of development",
       "Expect bugs, crashes and other nastiness",
       "-",
       "Still, have fun playing around"
    });
}


Intro::Intro(Game* game):
    GameState("Intro", game),
    m_scene(new IntroScene(*this)),
    m_cameraDolly(new CameraDolly()),
    m_cameraHead(new CameraHead(m_cameraDolly.get())),
    m_overTrigger(new Trigger()),
    m_showCountdown(0.0f),
    m_currentLine(0),
    m_currentLetter(0)
{

}

Intro::~Intro() = default;

const Scene& Intro::scene() const {
    return *m_scene;
}

const CameraHead& Intro::cameraHead() const {
    return *m_cameraHead;
}

void Intro::update(float deltaSec) {
    m_letterCountdown += deltaSec;

    while (m_letterCountdown > 0.0f && m_currentLine < INTRO_LINES.size()) {
        m_letterCountdown -= 0.05;

        if (m_currentLetter >= INTRO_LINES[m_currentLine].size()) {
            m_currentLine++;
            m_currentLetter = 0;
        } else {
            while (m_currentLine >= m_lines.size()) {
                m_lines.push_back(std::string());
            }

            m_lines.back() += INTRO_LINES[m_currentLine][m_currentLetter];
            m_currentLetter++;
        }
    }

    if (m_currentLine >= INTRO_LINES.size()) {
        m_showCountdown -= deltaSec;
        if (m_showCountdown <= 0.0f) {
            m_overTrigger->trigger();
        }
    }
}

void Intro::onEntered() {
    m_showCountdown = 1.5f;
}

void Intro::onLeft() {

}

Trigger& Intro::overTrigger() {
    return *m_overTrigger;
}

std::list<std::string> Intro::lines() const {
    return m_lines;
}

