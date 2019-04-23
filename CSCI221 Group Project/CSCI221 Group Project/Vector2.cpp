#include "Vector2.h"

Vector2::Vector2 () : x (0), y (0) { }

Vector2::Vector2 (float x, float y) : x (x), y (y) { }

Vector2 Vector2::zero = Vector2 (0, 0);