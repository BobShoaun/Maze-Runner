#include "Game.h"

int main () {
	Game game;
	game.ConstructConsole (screenWidth, screenHeight, 8, 8);																										
	game.Start ();
}