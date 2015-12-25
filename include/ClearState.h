#ifndef _ClearState_
#define _ClearState_

#include "GameState.h"
#include "MenuButton.h"

class ClearState : public GameState {
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void resume();

	virtual std::string getStateID() const {
		return m_clearID;
	}

private:
	static void s_clearToMain();

	static const std::string m_clearID;
	SDLGameObject *m_background;
	MenuButton *m_button;
};

#endif /* ClearState */
