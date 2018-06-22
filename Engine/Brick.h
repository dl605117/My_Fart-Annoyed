#pragma once
#include "RectF.h"
#include "Graphics.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF rect);
	void Draw( Graphics& gfx) const;
public:
	RectF rect;
	Color c;
	bool destroyed = false;
};