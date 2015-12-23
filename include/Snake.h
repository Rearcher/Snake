#ifndef _Snake_
#define _Snake_

#include "SDLGameObject.h"
#include <vector>
#include <iostream>

struct TurnPoint {
	Vector2D position;
	Vector2D velocity;

	TurnPoint(Vector2D pos, Vector2D v) {
		position = pos;
		velocity = v;
	}
};

class Snake : public SDLGameObject {
public:

	Snake() : SDLGameObject() {}

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams *pParams);

	Vector2D getLastVelocity() { return m_lastVelocity; }
	Vector2D getVelocity() { return m_velocity; }
	
	Vector2D getPosition() { return m_position; }

	void setLastVelocity(Vector2D v) { m_lastVelocity = v; }
	void setVelocity(Vector2D v) { m_velocity = v; }

	void updatePosition() {
		SDLGameObject::update();
	}
	
	static void cleanTurnPoints() {
		m_turnPoints.clear();
	}

	void bodyUpdate() {
		if (m_turnPoints.empty() || turnIndex >= m_turnPoints.size()) 
			return;
		
		if (m_position == m_turnPoints[turnIndex].position) {
			m_velocity = m_turnPoints[turnIndex].velocity;
			turnIndex++;
		}
	}
private:
	
	void handleInput();
	Vector2D m_lastVelocity;
	
	static std::vector<TurnPoint> m_turnPoints;
	int turnIndex;
};

#endif
