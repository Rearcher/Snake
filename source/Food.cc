#include "Food.h"

void Food::load(const LoaderParams *pParams) {
	SDLGameObject::load(pParams);
	m_currentFrame = 0;
}

void Food::draw() {
	SDLGameObject::draw();
}

void Food::clean() {

}

void Food::update() {
	SDLGameObject::update();	
}
