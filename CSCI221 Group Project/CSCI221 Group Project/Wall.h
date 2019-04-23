#pragma once
#include "GameObject.h"
#include "Game.h"

class Wall : public GameObject {

	public:

	Wall (Vector2 position, Vector2 dimensions, short color) : GameObject (position, dimensions, color) {

	}

	void onCollision (GameObject* col) {

	}

	void onUpdate (float deltaTime) {
		Game::engine->Fill (position.x, position.y, getEndPos ().x, getEndPos ().y, PIXEL_SOLID, color);

	}

};