#include "gameplayinput.h"

void GamePlayInput::resizeEvent(const unsigned int width, const unsigned int height) {
}

/*
 * Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles
 * This only applies for menu events etc, for action events set the toggleAction attribute to true
 */
void GamePlayInput::keyCallback(int key, int scancode, int action, int mods) {
}


void GamePlayInput::mouseButtonCallback(int button, int action, int mods) {
}

/*
 *  Check here for every-frame events, e.g. view & movement controls
 */
void GamePlayInput::update(float deltaSec) {
}
