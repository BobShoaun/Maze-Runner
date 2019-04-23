#pragma once

struct Vector2 {

	public:
	static Vector2 zero;
	float x, y;
	Vector2 ();
	Vector2 (float, float);
	bool operator == (const Vector2 & vector2) const {
		return x == vector2.x && y == vector2.y;
	}
	bool operator != (const Vector2 & vector2) const {
		return !(*this == vector2);
	}

	Vector2 operator + (const Vector2 & vector2) const {
		return Vector2 (this->x + vector2.x, this->y + vector2.y);
	}

};