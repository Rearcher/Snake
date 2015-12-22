#ifndef _SDLGameObject_
#define _SDLGameObject_

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject {
public:

	SDLGameObject() : GameObject() {}

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams *pParams);

	Vector2D &getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:

	Vector2D m_position;
	int m_width, m_height;
	int m_currentRow, m_currentFrame;
	std::string m_textureID;

	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_numFrames;
};

#endif /* SDLGameObject */
