/*
	@authur Ng Bob Shoaun
	@lastModified 24/4/2019
	@description Portal class
*/

#pragma once
#include "GameObject.h"

class Portal : public GameObject {

	public:
	Portal (Vector2 position, Vector2 dimensions, short color); // constructor
	void onUpdate (float deltaTime); // overriding virtual function

};

Portal::Portal (Vector2 position, Vector2 dimensions, short color)
	: GameObject (position, dimensions, color) {
}

void Portal::onUpdate (float deltaTime) {
	if (Game::game->portalVisible) // if portal is not visible, make it look like a wall
		Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, color);
	else
		Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, BG_BLACK);
}