#ifndef _PlayState_
#define _PlayState_

#include "Snake.h"
#include "Food.h"
#include "GameState.h"
#include "Map.h"
#include <vector>

const int body_size = 33;
const int food_size = 33;

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
	bool bodyCollision(SDLGameObject *p1, SDLGameObject *p2);
	bool checkBodyCollision();
	
	void produceFood();
	void bodyIncrease();

	bool isInsideBody(Vector2D);
private:

	static const std::string s_playID;

	Snake *m_head;
	std::vector<Snake*> m_body;

	Food *m_food;
	int foodTime;

	Map *m_map;
};

#endif /* PlayState */
