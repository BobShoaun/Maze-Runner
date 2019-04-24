#pragma once
#include "GameObject.h"

class Portal : public GameObject {

	public:

	Portal (Vector2 position, Vector2 dimensions, short color);
	void onUpdate (float deltaTime);

};

Portal::Portal (Vector2 position, Vector2 dimensions, short color)
	: GameObject (position, dimensions, color) {
}

void Portal::onUpdate (float deltaTime) {
	if (Game::game->portalVisible)
		Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, color);
	else
		Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, BG_BLACK);
}