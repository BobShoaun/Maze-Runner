/*
	@authur Ng Bob Shoaun
	@lastModified 24/4/2019
	@description Player class which contains movement and collision decisions logic
*/

#pragma once
#include "GameObject.h"

class Player : public GameObject {

	private:
	float penaltyDuration = 1.0f; // penalty time if player collides with map
	float penaltyTimer = penaltyDuration;
	float penaltySpeed = 15; // speed variables
	float normalSpeed = 20;
	float speed = normalSpeed;
	bool runner; // is runner or chaser?

	public:
	Player (Vector2 position, Vector2 dimensions, short color, bool r, float normalSpeed); // constructor

	void onCollision (GameObject* col); // overriding virtual functions
	void onUpdate (float deltaTime);

};

#include "Map.h"

Player::Player (Vector2 position, Vector2 dimensions, short color, bool r, float normalSpeed)
	: GameObject (position, dimensions, color), runner (r), normalSpeed (normalSpeed) { }

void Player::onCollision (GameObject* other) {

	if (dynamic_cast<Map *> (other)) { // if collided with the map
		setPosition (previousPosition);
		if (runner) // slows runner down only
			penaltyTimer = 0;
	}
	if (dynamic_cast<Player *> (other)) { // if collided with other player
		setPosition (previousPosition);
		Game::game->chaserWin = true; //chaser wins

	}
	Portal* p = dynamic_cast<Portal *> (other); // if collided with the portal
	if (p) {
		if (runner && Game::game->portalVisible) // if its a runner and the portal is active
			Game::game->runnerWin = true; // runner wins
		else
			setPosition (previousPosition);
	}
}

void Player::onUpdate (float deltaTime) {

	// calculations for the short movement penalty
	if (penaltyTimer < penaltyDuration) {
		speed = penaltySpeed;
		penaltyTimer += deltaTime;
	}
	else
		speed = normalSpeed;

	Vector2 newPosition = position;

	if (runner) { // runner controls
		if (Game::game->GetKey (VK_UP).bHeld)
			newPosition.y -= speed * deltaTime; // multiply by deltaTime (time between each frame) for frame rate independance

		if (Game::game->GetKey (VK_DOWN).bHeld)
			newPosition.y += speed * deltaTime;

		if (Game::game->GetKey (VK_LEFT).bHeld)
			newPosition.x -= speed * deltaTime;

		if (Game::game->GetKey (VK_RIGHT).bHeld)
			newPosition.x += speed * deltaTime;
	} // chaser controls
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
	// draw player
	Game::game->Fill (position.x, position.y, getEndPosition ().x, getEndPosition ().y, PIXEL_SOLID, color);
}