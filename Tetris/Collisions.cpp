#include "Collisions.h"

Collisions* Collisions::mInstance = nullptr;

Collisions::Collisions()
{
	//EMPTY
}

Collisions::~Collisions()
{
	mInstance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.y + rect1.height > rect2.y)
		return true;

	return false;
}