#pragma once
#include <vector>
#include "Vector2.h"

class GameObject {

	private:

	static int currentId;
	static std::vector<GameObject *> colliders;

	Vector2 initialPosition;

	void checkCollisionMatrix ();
	void clear (Vector2 position);
	
	protected:

	static std::vector<std::vector<int>> collisionMatrix;

	short color;
	int id;

	Vector2 position, previousPosition;
	Vector2 dimensions;
	Vector2 getEndPosition ();
	void setPosition (Vector2 position);

	virtual void updateCollisionMatrix ();
	virtual void onCollision (GameObject *);

	public:

	static void initializeCollisionMatrix (int width, int height);
	static void clearMatrix ();

	GameObject (Vector2 position, Vector2 dimensions);
	GameObject (Vector2 position, Vector2 dimensions, short color);

	virtual void onUpdate (float deltaTime) = 0;
	virtual void onReset ();
	
};

int GameObject::currentId = 1;

std::vector<std::vector<int>> GameObject::collisionMatrix;

std::vector<GameObject *> GameObject::colliders;

void GameObject::initializeCollisionMatrix (int width, int height) { 
	collisionMatrix.resize (width);
	for (int i = 0; i < width; i++)
		collisionMatrix [i].resize (height);
}

void GameObject::clearMatrix () { 
	for (int x = 0; x < collisionMatrix.size (); x++)
		for (int y = 0; y < collisionMatrix.front ().size (); y++)
				collisionMatrix [x] [y] = 0;
}

GameObject::GameObject (Vector2 position, Vector2 dimensions) : GameObject (position, dimensions, BG_WHITE) { }

GameObject::GameObject (Vector2 position, Vector2 dimensions, short color)
	: position (position), dimensions (dimensions), color (color) {
	colliders.push_back (this);
	id = currentId++;
	initialPosition = position;
	setPosition (position);
}

Vector2 GameObject::getEndPosition () {
	return position + dimensions;
}

void GameObject::onCollision (GameObject *) { };

void GameObject::onReset () {
	clear (previousPosition);
	setPosition (initialPosition);
}

void GameObject::setPosition (Vector2 position) {
	previousPosition = this->position;
	this->position = position;
	checkCollisionMatrix ();
}

void GameObject::checkCollisionMatrix () {
	for (int x = (int) position.x; x < (int) (position.x + dimensions.x); x++) {
		for (int y = (int) position.y; y < (int) (position.y + dimensions.y); y++) {
			int point = collisionMatrix [x] [y];
			if (point != 0 && point != id) {
				onCollision (colliders [point - 1]);
				return;
			}
		}
	}
	clear (previousPosition);
	updateCollisionMatrix ();
}

void GameObject::updateCollisionMatrix () {
	for (int x = (int) position.x; x < (int) (position.x + dimensions.x); x++)
		for (int y = (int) position.y; y < (int) (position.y + dimensions.y); y++)
			collisionMatrix [x] [y] = id;
}

void GameObject::clear (Vector2 position) {
	for (int x = (int) position.x; x < (int) (position.x + dimensions.x); x++)
		for (int y = (int) position.y; y < (int) (position.y + dimensions.y); y++)
			if (collisionMatrix [x] [y] == id)
				collisionMatrix [x] [y] = 0;
}