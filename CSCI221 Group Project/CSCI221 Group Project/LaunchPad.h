#pragma once
#include "GameObject.h"
#include "Game.h"

class LaunchPad : public GameObject {

	public:
	bool start;

	LaunchPad (Vector2 position, Vector2 dimensions, short color, bool s)
		: GameObject (position, dimensions, color) {
		start = s;
	
	}

	void onStart () { 
		
	}

	void onUpdate (float deltaTime) { 
		Game::engine->Fill (position.x, position.y, getEndPos ().x, getEndPos ().y, PIXEL_SOLID, color);
	}

};
