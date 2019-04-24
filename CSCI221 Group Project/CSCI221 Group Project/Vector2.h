#pragma once

struct Vector2 {
	public:
	float x, y;
	Vector2 ();
	Vector2 (float, float);
	bool operator == (const Vector2 & other) const;
	bool operator != (const Vector2 &) const;
	Vector2 operator + (const Vector2 &) const;
};

Vector2::Vector2 () : x (0), y (0) { }

Vector2::Vector2 (float x, float y) : x (x), y (y) { }

bool Vector2::operator == (const Vector2 & other) const {
	return x == other.x && y == other.y;
}

bool Vector2::operator != (const Vector2 & other) const {
	return !(*this == other);
}

Vector2 Vector2::operator + (const Vector2 & other) const {
	return Vector2 (this->x + other.x, this->y + other.y);
}