#pragma once
#include "GameObject.h"

class LaunchPad : public GameObject {

	public:

	bool start;
	LaunchPad (Vector2 position, Vector2 dimensions, short color, bool s);
	void onUpdate (float deltaTime);

};

LaunchPad::LaunchPad (Vector2 position, Vector2 dimensions, short color, bool s)
	: GameObject (position, dimensions, color) {
	start = s;
}

void LaunchPad::onUpdate (float deltaTime) {
	Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, color);
}