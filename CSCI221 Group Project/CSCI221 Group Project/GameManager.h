#pragma once
#include "GameObject.h"
#include "GameEngine.h"

class GameManager : public GameObject {

	public:

	void onCollision (GameObject* collider) {

	}

	void onUpdate (float deltaTime) {

		GameEngine::engine->Fill (position.x, position.y, getEndPos ().x, getEndPos ().y, PIXEL_SOLID, color);
	}

};