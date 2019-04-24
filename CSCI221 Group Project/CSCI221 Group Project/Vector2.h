/*
	@authur Ng Bob Shoaun
	@lastModified 24/4/2019
	@description Vector2 struct which contains x and y paired variables, useful in holding positions and dimensions.
*/

#pragma once

struct Vector2 {

	public:

	float x, y;

	Vector2 (); // constructors
	Vector2 (float, float);

	bool operator == (const Vector2 & other) const; // overloaded conditional and arithmetic operators
	bool operator != (const Vector2 &) const;
	Vector2 operator + (const Vector2 &) const;

};

Vector2::Vector2 () : x (0), y (0) { }

Vector2::Vector2 (float x, float y) : x (x), y (y) { }

bool Vector2::operator == (const Vector2 & other) const {
	return x == other.x && y == other.y;
}

bool Vector2::operator != (const Vector2 & other) const {
	return !(*this == other); // the opposite of == operator
}

Vector2 Vector2::operator + (const Vector2 & other) const {
	return Vector2 (this->x + other.x, this->y + other.y);
}