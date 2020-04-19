/*
	@authur Ng Bob Shoaun
	@lastModified 24/4/2019
	@description Map which is a GameObject, hold definitions for creating a map
*/

#pragma once
#include "GameObject.h"

class Map : public GameObject {

	private:
	std::vector < std::vector <char>> map; // 2d character array

	public:
	Map (std::vector < std::vector <char>> map, short color); // constructor

	void onReset (); // overriding virtual functions
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
		for (int y = 0; y < screenHeight; y++) // tile based map, size of each square tile is define by tileSize
			if (map [x / tileSize] [y / tileSize] == 'X' || map [x / tileSize] [y / tileSize] == 'x')
				collisionMatrix [x] [y] = id; // add obstacle to the collision matrix if character is an X
}

void Map::onUpdate (float deltaTime) {
	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++) 
			if (map [x / tileSize] [y / tileSize] == 'X' || map [x / tileSize] [y / tileSize] == 'x')
				Game::game->Draw (x, y, PIXEL_SOLID, color); // draw obstacle if character is X
}