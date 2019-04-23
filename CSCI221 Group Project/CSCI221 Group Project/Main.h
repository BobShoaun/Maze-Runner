#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "Wall.h"
#include "Player.h"
#include "Game.h"
#include "LaunchPad.h"


int main () {

	Game game;
	game.ConstructConsole (Game::screenWidth, Game::screenHeight, 8, 8);

	game.addGameObject (new LaunchPad (Vector2 (screenWidth - 20, 10), Vector2 (10, 10), FG_GREEN));
	game.addGameObject (new Player (Vector2 (6, screenHeight - 15), Vector2 (3, 3), FG_RED)); // runner
	game.addGameObject (new Player (Vector2 (6, screenHeight - 10), Vector2 (3, 3), FG_MAGENTA)); // chaser
	game.addGameObject (new Wall (Vector2 (10, 10), Vector2 (20, 10), FG_BLACK));
	game.addGameObject (new Wall (Vector2 (60, 70), Vector2 (20, 3), FG_DARK_YELLOW));
		
	game.Start ();
}
