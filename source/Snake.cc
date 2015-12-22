#include "Snake.h"
#include "InputHandler.h"

void Snake::load(const LoaderParams *pParams) {
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	m_velocity = Vector2D(1, 0);
}

void Snake::draw() {
	SDLGameObject::draw();
}

void Snake::update() {
	handleInput();
	SDLGameObject::update();
}

void Snake::clean() {

}

void Snake::handleInput() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
		m_velocity = Vector2D(1, 0);
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
		m_velocity = Vector2D(-1, 0);
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
		m_velocity = Vector2D(0, -2);
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		m_velocity = Vector2D(0, 2);

}
