#ifndef _PlayState_
#define _PlayState_

#include "SDLGameObject.h"
#include "GameState.h"
#include <vector>

class PlayState : public GameState {
public:

	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void resume();

	virtual std::string getStateID() const {
		return s_playID;
	}

	bool checkBorderCollision(SDLGameObject *p1);

private:

	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
};

#endif /* PlayState */
