/*
	@authur Ng Bob Shoaun, Tay Sui Jiet, Lim Kang Wei
	@lastModified 24/4/2019
	@description Game class containing game logic, states and the main game loop.
*/

#pragma once
#include <fstream>
#include <string>
#include <stdexcept>
#include "olcConsoleGameEngine.h"
#include "GameObject.h"

// screen width and height globals variables
int static const screenWidth = 120, screenHeight = 80;
int static const tileSize = 8; // tileSize must be a common multiple of both screen width and height

// inherits from external library olcConsoleGameEngine which contains the fundamentals to console games
// like the game loop and rendering graphics.
class Game : public olcConsoleGameEngine { 

	private:

	std::vector<GameObject*> gameObjects; // vector array containing all game objects
	std::vector < std::vector < std::vector <char>>> levels; // vector array containing all levels
	std::vector<int> levelPortalVisibleDurations; // vector array containing level portal open durations for each level

	olcSprite * chaserTextSprite = nullptr; // Sprites of texts for displaying after a round ends
	olcSprite * winsTextSprite = nullptr;
	olcSprite * runnerTextSprite = nullptr;

	float headStartTimer = 0.0f; // level specific variables
	float headStartDuration = 2.5f;

	float portalVisibleTimer = 0.0f;
	float portalVisibleDuration = 10;

	int currentLevelIndex = 0;

	void loadLevelMap (std::string path, int portalAppearDuration); // loads map from file into memory
	void loadLevel (int levelIndex); // loads level into screen
	void loadNextLevel ();
	void unloadLevel (); // properly unloads current level
	void reset (); // reset all temporary level variables

	bool OnUserCreate (); // overriden callback function when game starts
	bool OnUserUpdate (float deltaTime); // overriden callback function called each frame
	bool OnUserDestroy (); // overriden callback function when game ends

	public:

	static Game * game; // static field containing singleton instance of game

	bool chaserWin = false; // level specific variables
	bool runnerWin = false;
	bool chaserReleased = false;
	bool portalVisible = false;
};

#include "Portal.h"
#include "Player.h"

Game * Game::game;

void Game::loadLevelMap (std::string path, int portalAppearDuration) { 

	levelPortalVisibleDurations.push_back (portalAppearDuration);

	std::vector<std::vector<char>> map; // creating map 2d vector and resizing it accordingly
	map.resize (screenWidth / tileSize);
	for (int i = 0; i < screenWidth / tileSize; i++)
		map [i].resize (screenHeight / tileSize);

	std::ifstream mapFile (path); // get map text file
	if (!mapFile) { // file not found
		throw std::runtime_error ("Error Loading Map File");
		return;
	}
	else {
		for (int y = 0; y < screenHeight / tileSize; y++) {
			std::string line;
			std::getline (mapFile, line);
			for (int x = 0; x < screenWidth / tileSize; x++)
				map [x] [y] = line [x]; // assigning map from file to map 2d vector
		}
	}

	levels.push_back (map); // adding newly read map to levels
}

void Game::loadLevel (int levelIndex) {
	unloadLevel (); // unload current level first before loading new
	std::vector < std::vector <char>> map = levels [levelIndex]; // get current map from levels vector
	portalVisibleDuration = levelPortalVisibleDurations [levelIndex];

	gameObjects.push_back (new Map (map, BG_BLACK)); // generate map

	for (int x = 0; x < screenWidth / tileSize; x++) {
		for (int y = 0; y < screenHeight / tileSize; y++) {
			if (map [x] [y] == 'F' || map [x] [y] == 'f') // generate portal at F character
				gameObjects.insert (gameObjects.begin (), 
									new Portal (Vector2 (x * tileSize, y * tileSize), Vector2 (tileSize, tileSize), FG_GREEN));
			
			if (map [x] [y] == 'R' || map [x] [y] == 'r') // spawn runner at R character
				gameObjects.push_back ( // runner is blue in color
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_BLUE, true, 20)); // runner
			
			if (map [x] [y] == 'C' || map [x] [y] == 'c') // spawn chaser at C character
				gameObjects.push_back ( // chaser is red in color and slightly faster
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_RED, false, 22)); // chaser
			
		}
	}
}

void Game::loadNextLevel () { 
	if (currentLevelIndex < levels.size () - 1) {
		currentLevelIndex++; // increase level index
		loadLevel (currentLevelIndex);
	}
}

void Game::unloadLevel () {
	for (GameObject* gameObject : gameObjects) // free memory from pointer array
		delete gameObject;
	gameObjects.clear ();
	GameObject::clearMatrix ();
}

void Game::reset () {
	for (GameObject* gameObject : gameObjects) // reset all game objects
		gameObject->onReset ();
	chaserWin = false; // reset level variables
	runnerWin = false;
	chaserReleased = false;
	headStartTimer = 0;
	portalVisible = false;
	portalVisibleTimer = 0;
}

bool Game::OnUserCreate () {

	game = this; // setting instance to current and only instance (singleton)

	GameObject::initializeCollisionMatrix (screenWidth, screenHeight);

	loadLevelMap ("Levels/Level 1.txt", 0); // Load levels from file to memory
	loadLevelMap ("Levels/Level 2.txt", 10);
	loadLevelMap ("Levels/Level 3.txt", 15);
	loadLevelMap ("Levels/Level 4.txt", 10);
	loadLevelMap ("Levels/Level 5.txt", 15);

	// Load sprites from file to memory
	chaserTextSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Chaser.spr");
	winsTextSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Wins.spr");
	runnerTextSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Runner.spr");

	loadLevel (0); // load first level

	return true;
}

bool Game::OnUserUpdate (float deltaTime) {

	if (chaserWin) { // if chaser wins
		if (GetKey (VK_SPACE).bPressed)
			reset ();
		// draw Chaser Wins text
		DrawString (screenWidth / 2 - 11, screenHeight / 2, L"PRESS SPACE TO RESTART");
		DrawSprite (35, 30, chaserTextSprite);
		DrawSprite (15 + chaserTextSprite->nWidth, 30, winsTextSprite);
		return true;
	}

	if (runnerWin) { // if runner wins
		if (GetKey (VK_SPACE).bPressed) {
			reset ();
			loadNextLevel (); // load next level if runner wins
		}
		// draw runner Wins text
		DrawString (screenWidth / 2 - 15, screenHeight / 2, L"PRESS SPACE TO ENTER NEXT LEVEL");
		DrawSprite (35, 30, runnerTextSprite);
		DrawSprite (20 + runnerTextSprite->nWidth, 30, winsTextSprite);
		return true;
	}
	
	// calculation for headstart runner gets
	if (headStartTimer < headStartDuration)
		headStartTimer += deltaTime;
	else
		chaserReleased = true;

	// calculation for delay till portal becomes visible
	if (portalVisibleTimer < portalVisibleDuration)
		portalVisibleTimer += deltaTime;
	else
		portalVisible = true;

	// print Background
	Fill (0, 0, screenWidth, screenHeight, PIXEL_SOLID, FG_CYAN);

	for (GameObject* gameObject : gameObjects) // update all game objects each frame
		gameObject->onUpdate (deltaTime);

	return true;
}


bool Game::OnUserDestroy () {
	unloadLevel ();
	return true;
}