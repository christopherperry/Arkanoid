#pragma once

#include "Vector2.h"

struct Hit
{
	// The point of contact between the two objects during a collision.
	Vector2 contactPoint;

	// The surface normal at the point of contact.
	Vector2 normal;

	// The overlap between the two objects. Can be added to the colliding
	// object's position to move it back to a non-colliding state.
	Vector2 delta;
};

