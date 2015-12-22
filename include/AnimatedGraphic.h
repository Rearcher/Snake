#ifndef _AnimatedGraphic_
#define _AnimatedGraphic_

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject {
public:
	AnimatedGraphic() : SDLGameObject() {
		
	}
	
	void load(const LoaderParams *pParams) {
		SDLGameObject::load(pParams);
		m_animSpeed = pParams->getAnimSpeed(); 
	}

	void draw() {
		SDLGameObject::draw();
	}

	void clean() {

	}

	void update() {
		m_currentFrame = (int)((SDL_GetTicks() / (1000/m_animSpeed)) % m_numFrames);
	}

private:
	int m_animSpeed;
};

#endif /* AnimatedGraphic */
