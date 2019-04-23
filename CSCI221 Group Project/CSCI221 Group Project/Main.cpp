#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "Player.h"
#include "Game.h"
#include "LaunchPad.h"
#include "Map.h"

int main () {

	Game game;
	game.ConstructConsole (screenWidth, screenHeight, 8, 8);

	char map [screenWidth / 8] [screenHeight / 8] { {'0','0','0','0','0','0','0','0','0','0'},
													{'0','0','0','0',' ',' ','0','0','S','0'},
													{'0','0',' ',' ',' ',' ',' ','0',' ','0'},
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
													{'0','0','0','0','0','0','0','0','0','0'}, };
																													

	game.addGameObject (new Map (map));

	for (int x = 0; x < screenWidth / 8; x++) {
		for (int y = 0; y < screenHeight / 8; y++) {
			if (map [x] [y] == 'F') {

				game.addGameObjectToFront (new LaunchPad (Vector2 (x * 8, y * 8), Vector2 (8, 8), FG_GREEN, false));
			}
			if (map [x] [y] == 'S') {
				//game.addGameObject (new LaunchPad (Vector2 (x * 8, y * 8), Vector2 (8, 8), FG_YELLOW, true));
				
				game.addGameObject (new Player (Vector2 (5 + x * 8, 3 + y * 8), Vector2 (3, 3), FG_BLUE)); // runner
				game.addGameObject (new Player (Vector2 (x * 8, 3 + y * 8), Vector2 (3, 3), FG_RED)); // chaser
			}
		
		}
	}

	game.Start ();

}