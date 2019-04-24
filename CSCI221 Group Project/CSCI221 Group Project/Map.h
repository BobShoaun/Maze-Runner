#pragma once
#include "GameObject.h"

class Map : public GameObject {

	private:
	std::vector < std::vector <char>> map;

	public:
	Map (std::vector < std::vector <char>> map, short color);

	void onReset ();

	void updateCollisionMatrix ();

	void onUpdate (float deltaTime);

};

Map::Map (std::vector < std::vector <char>> map, short color)
	: GameObject (Vector2 (), Vector2 (), color), map (map) {
	updateCollisionMatrix ();
}

void Map::onReset () {
	updateCollisionMatrix ();
}

void Map::updateCollisionMatrix () {
	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			if (map [x / tileSize] [y / tileSize] == '0')
				collisionMatrix [x] [y] = id;
}

void Map::onUpdate (float deltaTime) {
	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			if (map [x / tileSize] [y / tileSize] == '0')
				Game::game->Draw (x, y, PIXEL_SOLID, color);
}