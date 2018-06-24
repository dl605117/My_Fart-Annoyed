#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick( const RectF& rect, Color c );
	void Draw( Graphics& gfx ) const;
	bool DoBallCollision( Ball& ball );
private:
	RectF rect;
	Color c;
	bool destroyed = false;
};