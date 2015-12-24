#ifndef _Map_
#define _Map_

#include "SDLGameObject.h"
#include <vector>
#include <string>
#include <fstream>

class Map {
public:
	Map() {}
	
	Map(std::string filename) {
		m_blockSize = 34;
		
		std::ifstream in(filename);
	    Vector2D v;
	    int temp1, temp2;

	    while (in >> temp1 >> temp2) {
	        v.setPoint(temp1, temp2);
	        m_parameters.push_back(v);
	    }   

	    in.close();

		std::cout << "map size: " <<
			m_parameters.size() << "\n";
	}

	void render();
	void update();
	
	bool load(std::string, std::string);

	bool isInside(Vector2D);

private:

	std::vector<SDLGameObject*> m_blocks;
	std::vector<Vector2D> m_parameters;
	
	std::string m_id;
	int m_blockSize;
};

#endif /* Map */
