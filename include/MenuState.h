#ifndef _MenuState_
#define _MenuState_

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState {
public:

	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void resume();

	virtual std::string getStateID() const {
		return s_menuID;
	}

private:

	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;

	static void s_menuToPlay();
	static void s_exitFromMenu();
};

#endif /* MenuState */
