
#include <GL/glew.h>

#include <glow/Error.h>
#include <glow/logging.h>
#include <glow/Timer.h>
#include <glowwindow/ContextFormat.h>
#include <glowwindow/Context.h>
#include <glowwindow/Window.h>
#include <glowwindow/WindowEventHandler.h>

#include <memory>
#include <iostream>

#include "game.h"


class EventHandler : public glow::WindowEventHandler
{
public:
    EventHandler() : 
		m_game(),
		m_timer()
    {
    }

    virtual ~EventHandler()
    {
    }

	virtual void initializeEvent(glow::Window & window)
    {
		glow::DebugMessageOutput::enable();
		m_game.initialize();
		m_timer.reset();
    }
    
    virtual void resizeEvent(
		glow::Window & window
    ,   const unsigned int width
    ,   const unsigned int height)
    {
		glViewport(0, 0, width, height);
		m_game.resizeEvent(width, height);
        std::cout << "resize " << width << "x" << height << std::endl;
    }

	virtual void paintEvent(glow::Window & window)
    {
		float delta = static_cast<float>(m_timer.elapsed() / 1000000000.0);
		m_timer.reset();

		m_game.update(delta);
		m_game.draw();
    }

	virtual void idleEvent(glow::Window & window)
    {
        window.repaint();
    }

    virtual void keyPressEvent(glow::Window & window, glow::KeyEvent & event) {
        switch (event.key())
        {
        case glow::KeyEvent::KeyF5:
            glow::ShaderFile::reloadAll();
            break;
        default:
            break;
        }
    }

    virtual void keyReleaseEvent(glow::Window & window, glow::KeyEvent & event) {

    }

protected:
	Game m_game;
	glow::Timer m_timer;
    
};


/** This example shows ... .
*/
int main(int argc, char** argv)
{
    glewExperimental = GL_TRUE;

	glow::ContextFormat format;

	glow::Window window;
    window.assign(new EventHandler());

    window.create(format, "Simple Texture Example");
	window.context()->setSwapInterval(glow::Context::AdaptiveVerticalSyncronization);
	window.show();

	return glow::Window::run();
}


