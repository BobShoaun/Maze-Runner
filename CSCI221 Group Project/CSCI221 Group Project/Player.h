#pragma once
#include "GameObject.h"

class Player : public GameObject {

	private:

	float penaltyDuration = 1.0f;
	float penaltyTimer = penaltyDuration;

	float penaltySpeed = 15;
	float normalSpeed = 20;
	float speed = normalSpeed;

	bool runner; // is runner or chaser?

	public:

	Player (Vector2 position, Vector2 dimensions, short color, bool r, float normalSpeed);

	void onCollision (GameObject* col);

	void onUpdate (float deltaTime);

};

#include "Map.h"

Player::Player (Vector2 position, Vector2 dimensions, short color, bool r, float normalSpeed)
	: GameObject (position, dimensions, color), runner (r), normalSpeed (normalSpeed) { }

void Player::onCollision (GameObject* col) {

	if (dynamic_cast<Map *> (col)) {
		setPosition (previousPosition);
		if (runner)
			penaltyTimer = 0;
	}
	if (dynamic_cast<Player *> (col)) {
		setPosition (previousPosition);
		Game::game->chaserWin = true; //chaser wins

	}
	LaunchPad* p = dynamic_cast<LaunchPad *> (col);
	if (p && !p->start) {
		if (runner) // runner wins
			Game::game->runnerWin = true;
		else
			setPosition (previousPosition);
	}
}

void Player::onUpdate (float deltaTime) {

	if (penaltyTimer < penaltyDuration) {
		speed = penaltySpeed;
		penaltyTimer += deltaTime;
	}
	else
		speed = normalSpeed;

	Vector2 newPosition = position;

	if (runner) {

		if (Game::game->GetKey (VK_UP).bHeld)
			newPosition.y -= speed * deltaTime;

		if (Game::game->GetKey (VK_DOWN).bHeld)
			newPosition.y += speed * deltaTime;

		if (Game::game->GetKey (VK_LEFT).bHeld)
			newPosition.x -= speed * deltaTime;

		if (Game::game->GetKey (VK_RIGHT).bHeld)
			newPosition.x += speed * deltaTime;
	}
	else if (Game::game->chaserReleased) {

		if (Game::game->GetKey (87).bHeld) // w key
			newPosition.y -= speed * deltaTime;

		if (Game::game->GetKey (83).bHeld) // s key
			newPosition.y += speed * deltaTime;

		if (Game::game->GetKey (0x41).bHeld) // a key
			newPosition.x -= speed * deltaTime;

		if (Game::game->GetKey (0x44).bHeld) // d key
			newPosition.x += speed * deltaTime;
	}
	setPosition (newPosition);

	Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, color);
}