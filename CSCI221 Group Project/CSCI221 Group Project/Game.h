#pragma once
#include "olcConsoleGameEngine.h"
#include "GameObject.h"

int static const screenWidth = 120, screenHeight = 80;
int static const tileSize = 8;

class Game : public olcConsoleGameEngine { 

	private:
	std::vector<GameObject*> gameObjects;

	olcSprite * chaserSprite = nullptr;
	olcSprite * winsSprite = nullptr;
	olcSprite * runnerSprite = nullptr;

	std::vector < std::vector < std::vector <char>>> levels;
	int currentLevelIndex = 0;

	float headStartTimer = 0.0f;
	float headStartDuration = 2.5f;

	void loadLevel (std::vector < std::vector <char>> m);
	void loadNextLevel ();

	void unloadLevel ();

	bool OnUserCreate ();

	bool OnUserUpdate (float deltaTime);

	void reset ();

	bool OnUserDestroy ();

	public:

	static Game * game;

	bool chaserWin = false;
	bool runnerWin = false;
	bool chaserReleased = false;
	
};

#include "LaunchPad.h"
#include "Player.h"

Game * Game::game;

void Game::loadLevel (std::vector < std::vector <char>> map) {
	unloadLevel ();

	gameObjects.push_back (new Map (map, BG_BLACK));

	for (int x = 0; x < screenWidth / tileSize; x++) {
		for (int y = 0; y < screenHeight / tileSize; y++) {
			if (map [x] [y] == 'F')
				gameObjects.insert (gameObjects.begin (), 
									new LaunchPad (Vector2 (x * tileSize, y * tileSize), Vector2 (tileSize, tileSize), FG_GREEN, false));
			
			if (map [x] [y] == 'R')
				gameObjects.push_back (
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_BLUE, true, 20)); // runner
			
			if (map [x] [y] == 'C')
				gameObjects.push_back (
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_RED, false, 25)); // chaser
			
		}
	}
}

void Game::loadNextLevel () { 
	if (currentLevelIndex < levels.size () - 1) {
		currentLevelIndex++;
		loadLevel (levels [currentLevelIndex]);
	}
}

void Game::unloadLevel () {
	for (GameObject* gameObject : gameObjects)
		delete gameObject;
	gameObjects.clear ();
	GameObject::clearMatrix ();
}

bool Game::OnUserCreate () {

	game = this;

	GameObject::initializeCollisionMatrix (screenWidth, screenHeight);
	// Level 1
	levels.push_back ({ {'0','0','0','0','0','0','0','0','0','0'},
						{'0','0','0','0',' ',' ','0','0','C','0'},
						{'0','0',' ',' ',' ',' ',' ','0','R','0'},
						{'0',' ',' ','0','0','0',' ','0',' ','0'},
						{'0',' ',' ','0','0',' ',' ','0',' ','0'},
						{'0',' ','0','0',' ',' ',' ','0',' ','0'},
						{'0',' ',' ','0',' ',' ','0',' ',' ','0'},
						{'0','0',' ','0',' ','0',' ',' ','0','0'},
						{'0',' ',' ','0',' ','0',' ','0','0','0'},
						{'0',' ','0','0',' ','0',' ',' ','0','0'},
						{'0',' ',' ','0',' ',' ','0',' ',' ','0'},
						{'0','0',' ','0','0',' ',' ','0',' ','0'},
						{'0','0',' ','0','0','0',' ',' ',' ','0'},
						{'0','F',' ','0','0','0','0',' ','0','0'},
						{'0','0','0','0','0','0','0','0','0','0'}, });

	// Level 2
	levels.push_back ({ {'0','0','0','0','0','0','0','0','0','0'},
						{'0','0',' ','0',' ','0',' ','R','C','0'},
						{'0',' ',' ',' ',' ',' ',' ','0','0','0'},
						{'0',' ','0','0','0',' ','0','0',' ','0'},
						{'0',' ','0','0','0','0',' ',' ',' ','0'},
						{'0',' ','0','0',' ',' ',' ','0',' ','0'},
						{'0',' ',' ','0',' ',' ',' ','0',' ','0'},
						{'0','0',' ','0',' ','0','0','0',' ','0'},
						{'0',' ',' ','0',' ','0',' ','0',' ','0'},
						{'0',' ','0','0',' ','0',' ',' ',' ','0'},
						{'0',' ',' ','0',' ','0',' ','0','0','0'},
						{'0','0',' ','0',' ','0',' ','0','F','0'},
						{'0','0',' ','0',' ','0',' ',' ',' ','0'},
						{'0',' ',' ',' ',' ','0','0',' ','0','0'},
						{'0','0','0','0','0','0','0','0','0','0'}, });

	// Load sprites
	chaserSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Chaser.spr");
	winsSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Wins.spr");
	runnerSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Runner.spr");

	loadLevel (levels [0]); // load first level

	return true;
}

bool Game::OnUserUpdate (float deltaTime) {

	if (chaserWin) {
		if (GetKey (VK_SPACE).bPressed)
			reset ();
		
		DrawString (screenWidth / 2 - 11, screenHeight / 2, L"PRESS SPACE TO RESTART");
		DrawSprite (35, 30, chaserSprite);
		DrawSprite (15 + chaserSprite->nWidth, 30, winsSprite);
		return true;
	}

	if (runnerWin) {
		if (GetKey (VK_SPACE).bPressed) {
			reset ();
			loadNextLevel ();
		}
		DrawString (screenWidth / 2 - 15, screenHeight / 2, L"PRESS SPACE TO ENTER NEXT LEVEL");
		DrawSprite (35, 30, runnerSprite);
		DrawSprite (20 + runnerSprite->nWidth, 30, winsSprite);
		return true;
	}

	if (headStartTimer < headStartDuration)
		headStartTimer += deltaTime;
	else
		chaserReleased = true;

	// print Background
	Fill (0, 0, screenWidth, screenHeight, PIXEL_SOLID, FG_CYAN);

	for (GameObject* gameObject : gameObjects)
		gameObject->onUpdate (deltaTime);

	return true;
}

void Game::reset () {
	for (GameObject* gameObject : gameObjects)
		gameObject->onReset ();
	chaserWin = false;
	runnerWin = false;
	chaserReleased = false;
	headStartTimer = 0;
}

bool Game::OnUserDestroy () {
	unloadLevel ();
	return true;
}