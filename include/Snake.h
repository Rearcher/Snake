#ifndef _Snake_
#define _Snake_

#include "SDLGameObject.h"

class Snake : public SDLGameObject {
public:

	Snake() : SDLGameObject() {}

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams *pParams);
private:
	
	void handleInput();
};

#endif
