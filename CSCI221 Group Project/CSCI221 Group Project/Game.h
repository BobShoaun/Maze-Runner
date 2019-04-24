#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
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
	std::vector<int> levelPortalAppearDurations;
	int currentLevelIndex = 0;

	float headStartTimer = 0.0f;
	float headStartDuration = 2.5f;

	float portalAppearTimer = 0.0f;
	float portalAppearDuration = 10;

	void loadLevel (int levelIndex);
	void loadNextLevel ();

	void loadLevelMap (std::string path, int portalAppearDuration);
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
	bool portalVisible = false;
};

#include "Portal.h"
#include "Player.h"

Game * Game::game;

void Game::loadLevelMap (std::string path, int portalAppearDuration) { 

	levelPortalAppearDurations.push_back (portalAppearDuration);

	std::vector<std::vector<char>> mapV;
	mapV.resize (screenWidth / tileSize);
	for (int i = 0; i < screenWidth / tileSize; i++)
		mapV [i].resize (screenHeight / tileSize);

	std::ifstream map (path);
	if (!map) {
		throw std::runtime_error ("NOPE");
		return;
	}
	else {
		std::string line;
		for (int y = 0; y < screenHeight / tileSize; y++) {
			std::getline (map, line);
			for (size_t x = 0; x < screenWidth / tileSize; x++)
				mapV [x] [y] = line [x];
		}
	}

	levels.push_back (mapV);
}

void Game::loadLevel (int levelIndex) {
	unloadLevel ();
	std::vector < std::vector <char>> map = levels [levelIndex];
	portalAppearDuration = levelPortalAppearDurations [levelIndex];

	gameObjects.push_back (new Map (map, BG_BLACK));

	for (int x = 0; x < screenWidth / tileSize; x++) {
		for (int y = 0; y < screenHeight / tileSize; y++) {
			if (map [x] [y] == 'F' || map [x] [y] == 'f')
				gameObjects.insert (gameObjects.begin (), 
									new Portal (Vector2 (x * tileSize, y * tileSize), Vector2 (tileSize, tileSize), FG_GREEN));
			
			if (map [x] [y] == 'R' || map [x] [y] == 'r')
				gameObjects.push_back (
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_BLUE, true, 20)); // runner
			
			if (map [x] [y] == 'C' || map [x] [y] == 'c')
				gameObjects.push_back (
					new Player (Vector2 (3 + x * tileSize, 3 + y * tileSize), Vector2 (3, 3), FG_RED, false, 20)); // chaser
			
		}
	}
}

void Game::loadNextLevel () { 
	if (currentLevelIndex < levels.size () - 1) {
		currentLevelIndex++;
		loadLevel (currentLevelIndex);
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

	loadLevelMap ("Level 1.txt", 0);
	loadLevelMap ("Level 2.txt", 15);
	loadLevelMap ("Level 3.txt", 10);
	loadLevelMap ("Level 4.txt", 15);
	loadLevelMap ("Level 5.txt", 15);

	// Load sprites
	chaserSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Chaser.spr");
	winsSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Wins.spr");
	runnerSprite = new olcSprite (L"../CSCI221 Group Project/Sprites/Runner.spr");

	loadLevel (0); // load first level

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

	if (portalAppearTimer < portalAppearDuration)
		portalAppearTimer += deltaTime;
	else
		portalVisible = true;

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
	portalVisible = false;
	portalAppearTimer = 0;
}

bool Game::OnUserDestroy () {
	unloadLevel ();
	return true;
}