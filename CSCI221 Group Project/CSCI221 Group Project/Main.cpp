#include <iostream>
#include <conio.h>
#include <windows.h>
#include <array>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "Vector2.h"

using namespace std;

const int screenHeight = 25, screenWidth = 100;

array<array<char, screenWidth>, screenHeight> previousScreen;
array<array<char, screenWidth>, screenHeight> currentScreen;

/* toggles the underscore in the console to be visible or invisible depending on the boolean passed in
function is not original and copy pasted from the internet, as it is not part of the logic of the program */
void toggleConsoleCursor (bool isVisible) {
	HANDLE out = GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo (out, &cursorInfo);
	cursorInfo.bVisible = isVisible; // set the cursor visibility
	SetConsoleCursorInfo (out, &cursorInfo);
}

void draw (vector<vector<char>> obj, Vector2 pos) {
	
	//int rows = sizeof obj / sizeof obj [0];
	//int cols = sizeof obj [0] / sizeof (char);

	for (int objY = 0, y = pos.y; objY < obj.size (); y++, objY++) {
		for (int objX = 0, x = pos.x; objX < obj [0].size (); x++, objX++) {
			currentScreen [y] [x] = (obj) [objY] [objX];
		}
	}

}

int main () { 

	ifstream in ("Monster.txt");

	if (!in) { 
		cout << "Cannot open Monster file.\n";
		cin.get ();
		return 1;
	}

	vector<vector<char>> monster (20, vector<char> (30, 0));
	//char word [30];
	//for (int y = 0; y < 20; y++) {
		//for (int x = 0; x < 30; x++) {
			//string s;
			//getline (in, s);
			//char cstr [s.size () + 1];
			//strcopy (cstr, s.c_str ());
			//monster [y] = cstr;
			//in >> monster [y] [x];
		//}
	//}
	//draw (monster, Vector2 (2, 3));

	in.close ();


	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	if (!hConsole)
		return 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo (hConsole, &csbi);
	COORD coordCur = csbi.dwCursorPosition;

	toggleConsoleCursor (false);

	for (int height = 0; height < screenHeight; height++)
		for (int width = 0; width < screenWidth; width++)
			previousScreen [height] [width] = currentScreen [height] [width] = ' ';

	Vector2 pos (0, 0);

	vector<vector<char>> defaultPose = { { ' ', 'O', ' ' },
								 { '/', '|', 92 },
								 { '/', '`', 92 } };

	while (true) { 

		Sleep (100);

		if (_kbhit ()) {
			char input = _getch ();
			if (input == ' ')
				pos.x++;

		}

		for (int y = 0; y < screenHeight; y++)
			for (int x = 0; x < screenWidth; x++)
				currentScreen [y] [x] = ' ';

		draw (defaultPose, pos);

		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				if (previousScreen [y] [x] != currentScreen [y] [x]) { 
					coordCur.X = x;
					coordCur.Y = y;
					SetConsoleCursorPosition (hConsole, coordCur);
					cout << currentScreen [y] [x];
					previousScreen [y] [x] = currentScreen [y] [x];
					//currentScreen [y] [x] = ' ';
				}
			}
		}
		

		// and print any information from the new position
		//printf ("..."); // old text will be replaced

	}

	CloseHandle (hConsole);
	return 0; 
}

