#pragma once
#include <iostream>
#include "GameObject.h"
#include "Game.h"

class Map : public GameObject {

	private:
	char matrix [screenWidth / 8] [screenHeight / 8];

	public:
	Map (char m [screenWidth / 8] [screenHeight / 8])
		: GameObject (Vector2::zero, Vector2::zero) { 
		for (int x = 0; x < screenWidth / 8; x++) {
			for (int y = 0; y < screenHeight / 8; y++) {
				matrix [x] [y] = m [x] [y];
			}
		}
		updateCollisionMatrix ();
	}

	void onReset () { 
		updateCollisionMatrix ();
	}

	void updateCollisionMatrix () {
		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
				
				if (matrix [x / 8] [y / 8] == '0') {
					
					collisionMatrix [x] [y] = id;
				}
			}
		}
	}

	void onUpdate (float deltaTime) { 
		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
			
			
				if (matrix [x / 8] [y / 8] == '0')
					Game::engine->Draw (x, y, 9608, BG_BLACK);
			}
		}
		
	}


};