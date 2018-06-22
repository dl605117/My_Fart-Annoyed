#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF rect, Color c );
	void Draw( Graphics& gfx) const;
	bool DoBallCollision( Ball& ball);
public:
	RectF rect;
	Color c;
	bool destroyed = false;
};