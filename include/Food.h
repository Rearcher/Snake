#ifndef _Food_
#define _Food_

#include "SDLGameObject.h"

class Food : public SDLGameObject {
public:
	
	Food() : SDLGameObject() {}
	
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(const LoaderParams *pParams);
};

#endif /* _Food_ */
