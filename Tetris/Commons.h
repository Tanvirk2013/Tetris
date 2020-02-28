#pragma once

struct Vector2D
{
	float x;
	float y;
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;
	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width = initialWidth;
		height = initialHeight;
	}
};

enum SCREENS
{
	SCREEN_MENU,
	SCREEN_PLAY,
	SCREEN_GAMEOVER
};

enum SCREEN_STATE
{
	GAMEOVER,
	RUNNING
};

enum COLOURS
{
	CLEAR = 0,
	WHITE = 32,
	LBLUE = 64,
	DBLUE = 96,
	ORANGE = 128,
	YELLOW = 160,
	GREEN = 192,
	RED = 224,
	PURPLE = 256
};

enum SOUNDS
{
	SOUND_MOVE,
	SOUND_MENU,
	SOUND_PLAY
};

enum ROTATION
{
	LEFT = 90,
	RIGHT = -90
};