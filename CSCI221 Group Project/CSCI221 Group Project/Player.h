#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Game.h"
#include "LaunchPad.h"

class Player : public GameObject {

	private:
		static int count;

	public:
	int id;
	float speed = 20;
	float penaltyTimer = 2;

	Player (Vector2 position, Vector2 dimensions, short color)
		: GameObject (position, dimensions, color) {
		id = count++;
	}

	void onCollision (GameObject* col) {
		
		if (dynamic_cast<Map *> (col)) {
			setPosition (previousPosition);
			if (id == 0)
				penaltyTimer = 0;
		}
		if (dynamic_cast<Player *> (col)) { 
			setPosition (previousPosition); 
			Game::engine->over = true; //lose

		}
		LaunchPad* p = dynamic_cast<LaunchPad *> (col);
		if (p && !p->start) {
			if (id == 0) //win
				Game::engine->win = true;
			else
				setPosition (previousPosition);
		}
	}

	void onUpdate (float deltaTime) {

		if (penaltyTimer < 1.0f) {
			speed = 15;
			penaltyTimer += deltaTime;
		}
		else
			speed = 20;

		Vector2 newPos = position;

		if (id == 0) {

			if (Game::engine->GetKey (VK_UP).bHeld)
				newPos.y -= speed * deltaTime;

			if (Game::engine->GetKey (VK_DOWN).bHeld)
				newPos.y += speed * deltaTime;

			if (Game::engine->GetKey (VK_LEFT).bHeld)
				newPos.x -= speed * deltaTime;

			if (Game::engine->GetKey (VK_RIGHT).bHeld)
				newPos.x += speed * deltaTime;
		}
		else if (Game::engine->chaserReleased) {

			if (Game::engine->GetKey (87).bHeld)
				newPos.y -= speed * deltaTime;

			if (Game::engine->GetKey (83).bHeld)
				newPos.y += speed * deltaTime;

			if (Game::engine->GetKey (0x41).bHeld)
				newPos.x -= speed * deltaTime;

			if (Game::engine->GetKey (0x44).bHeld)
				newPos.x += speed * deltaTime;
		}
		setPosition (newPos);

		Game::engine->Fill (position.x, position.y, getEndPos ().x, getEndPos ().y, PIXEL_SOLID, color);
	}

};

int Player::count = 0;
