#pragma once

struct Vector2 {

	public:
	int x, y;
	Vector2 ();
	Vector2 (int, int);
	bool operator == (const Vector2 & vector2) const {
		return x == vector2.x && y == vector2.y;
	}
	bool operator != (const Vector2 & vector2) const {
		return !(*this == vector2);
	}

};