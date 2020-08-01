#pragma once

#include <string>
#include "../math/Vector2.h"

struct Hit
{
	// Tag of the Entity that was hit.
	std::string tag{"none"};

	// The point of contact between the two objects during a collision.
	Vector2 contactPoint{ 0.0f, 0.0f };

	// The surface normal at the point of contact.
	Vector2 normal{ 0.0f, 0.0f };

	// The overlap between the two objects. Can be added to the colliding
	// object's position to move it back to a non-colliding state.
	Vector2 delta{ 0.0f, 0.0f };

	// The velocity of the thing that was hit
	Vector2 velocity{ 0.0f, 0.0f };
};

