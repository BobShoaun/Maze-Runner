#pragma once
#include <vector>
#include "Vector2.h"

//int static const screenWidth = 160, screenHeight = 100;
int static const screenWidth = 120, screenHeight = 80;
//int static const screenWidth = 10, screenHeight = 10;

class GameObject {

	private:
	static int currentId;
	
	static std::vector<GameObject *> colliders;
	
	Vector2 initialPosition;

	protected:
	
	short color;
	int id;
	public:
	static int collisionMatrix [screenWidth] [screenHeight];
	GameObject (Vector2 position, Vector2 dimensions) 
		: position (position), dimensions (dimensions) {
		colliders.push_back (this);
		id = currentId++;
		initialPosition = position;
		setPosition (position);
	}

	GameObject (Vector2 position, Vector2 dimensions, short color) 
		: position (position), dimensions (dimensions), color (color) {
		colliders.push_back (this);
		id = currentId++;
		initialPosition = position;
		setPosition (position);
	}

	Vector2 position, previousPosition;
	Vector2 dimensions;

	Vector2 getEndPos () { 
		return position + dimensions;
	}

	virtual void onCollision (GameObject *) { };
	virtual void onStart () { }
	virtual void onUpdate (float deltaTime) = 0;
	virtual void onReset () { 
		clear (previousPosition);
		setPosition (initialPosition);
		
	}

	void setPosition (Vector2 position) {
		previousPosition = this->position;
		this->position = position;
		checkCollisionMatrix ();
	}

	void checkCollisionMatrix () {
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

	virtual void updateCollisionMatrix () {

		for (int x = (int) position.x; x < (int) (position.x + dimensions.x); x++)
			for (int y = (int) position.y; y < (int) (position.y + dimensions.y); y++)
				collisionMatrix [x] [y] = id;

	}

	void clear (Vector2 position) {
		for (int x = (int) position.x; x < (int) (position.x + dimensions.x); x++)
			for (int y = (int) position.y; y < (int) (position.y + dimensions.y); y++)
				if (collisionMatrix [x] [y] == id)
					collisionMatrix [x] [y] = 0;
	}

};

int GameObject::currentId = 1;

int GameObject::collisionMatrix [screenWidth] [screenHeight];

std::vector<GameObject *> GameObject::colliders;