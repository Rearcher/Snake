#ifndef _NextLevelState_
#define _NextLevelState_

#include "SDLGameObject.h"
#include "GameState.h"
#include "SDL2/SDL.h"
#include <string>

class NextLevelState : public GameState {
public:
	NextLevelState(std::string filename) : GameState(),
		m_filename(filename) {}

	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();

	virtual void resume();

	virtual std::string getStateID() const {
		return m_nextLevelID;
	}

private:
	Uint32 m_enterTime;
	std::string m_filename;
	
	static const std::string m_nextLevelID;	
	SDLGameObject *m_object;
};

#endif /* NextLevelState */
