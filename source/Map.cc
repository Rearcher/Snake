#include "Map.h"
#include "TextureManager.h"
#include "Game.h"

void Map::render() {
	for (auto block : m_blocks)
		block->draw();
}

void Map::update() {
	for (auto block : m_blocks)
		block->update();
}

bool Map::load(std::string filename, std::string id) {
	
	if (TheTextureManager::Instance()->load(filename, id,
				TheGame::Instance()->getRenderer())) {
		m_id = id;

		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			
			Vector2D vec = m_parameters[i];
			SDLGameObject *block = new SDLGameObject();
			block->load(new LoaderParams(vec.getX(), vec.getY(), m_blockSize,
						m_blockSize, m_id, 1));
			block->setCurrentFrame(4);
			
			m_blocks.push_back(block);
		}
		
		return true;
	}
	return false;
}

bool Map::isInside(Vector2D v) {
	float x = v.getX();
	float y = v.getY();

	for (auto block : m_blocks) {
		Vector2D pos = block->getPosition();

		if (x > pos.getX() && x < pos.getX()+m_blockSize
				&& y > pos.getY() && y < pos.getY()+m_blockSize)
			return true;
	}
	
	return false;
}
