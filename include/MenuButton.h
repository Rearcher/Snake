#ifndef _MenuButton_
#define _MenuButton_

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject {
public:

	MenuButton(void (*callback)()) : SDLGameObject(),
	m_callback(callback) {
		m_currentFrame = MOUSE_OUT;
	}

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams *pParams);

private:
	enum button_state {
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*m_callback) ();
	bool m_bReleased;
};

#endif /* MenuButton */
