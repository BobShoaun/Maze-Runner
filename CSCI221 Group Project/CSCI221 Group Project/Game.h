#pragma once
#include "olcConsoleGameEngine.h"
#include "GameObject.h"

class Game : public olcConsoleGameEngine { 

	private:
	std::vector<GameObject*> gameObjects;
	olcSprite * chaserSprite = nullptr;
	olcSprite * winsSprite = nullptr;
	olcSprite * runnerSprite = nullptr;

	public:

	//int static const screenWidth = 160, screenHeight = 120;
	static Game* engine;

	bool over = false;
	bool win = false;

	bool chaserReleased = false;
	float timer = 0.0f;

	void addGameObject (GameObject* col) { 
		gameObjects.push_back (col);
		
	}

	void addGameObjectToFront (GameObject* col) { 
		gameObjects.insert (gameObjects.begin (), col);
	}

	bool OnUserCreate () {

		chaserSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Chaser.spr");
		winsSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Wins.spr");
		runnerSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Runner.spr");
	
		engine = this;

		for (GameObject* gameObject : gameObjects) {
			gameObject->onStart ();
		}
		return true;
	}

	bool OnUserUpdate (float deltaTime) { 

		if (over) { 
			if (GetKey (VK_SPACE).bPressed) { 
				reset ();
			}

			DrawString (screenWidth / 2 - 11, screenHeight / 2, L"PRESS SPACE TO RESTART");
			DrawSprite (35, 30, chaserSprite);
			DrawSprite (15 + chaserSprite->nWidth, 30, winsSprite);
			return true;
		}

		if (win) { 
			if (GetKey (VK_SPACE).bPressed) {
				reset ();
			}
			DrawString (screenWidth / 2 - 11, screenHeight / 2, L"PRESS SPACE TO RESTART");
			DrawSprite (35, 30, runnerSprite);
			DrawSprite (20 + runnerSprite->nWidth, 30, winsSprite);
			return true;
		}

		if (timer < 2.5f)
			timer += deltaTime;
		else
			chaserReleased = true;

		// print Background
		Fill (0, 0, screenWidth, screenHeight, PIXEL_SOLID, FG_CYAN);
		
		for (GameObject* gameObject : gameObjects)
			gameObject->onUpdate (deltaTime);

		
		return true;
	}

	void reset () {
		for (GameObject* gameObject : gameObjects)
			gameObject->onReset ();
		over = false;
		win = false;
		chaserReleased = false;
		timer = 0;
	}

	bool OnUserDestroy () { 

		for (GameObject* gameObject : gameObjects) { 
			delete gameObject;
		}

		return true;
	}
	
};

Game* Game::engine;
