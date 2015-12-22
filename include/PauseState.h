#ifndef _PauseState_
#define _PauseState_

#include "GameState.h"
#include "GameObject.h"
#include <string>
#include <vector>

class PauseState : public GameState {
public:
	
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void resume();

	virtual std::string getStateID() const {
		return s_pauseID;
	}

private:

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};

#endif /* PauseState */
