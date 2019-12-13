#pragma once

#include "Commons.h"

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Box(Rect2D rect1, Rect2D rect2);
private:
	Collisions();
	
	static Collisions* mInstance;
};

