/*
	@authur Ng Bob Shoaun, Brendan Hoh
	@lastModified 24/4/2019
	@description Main function containing client code
*/

#include "Game.h"

int main () {
	Game game; // Creates game instance
	game.ConstructConsole (screenWidth, screenHeight, 8, 8); // defining window and font size
	game.Start (); // starting game
}