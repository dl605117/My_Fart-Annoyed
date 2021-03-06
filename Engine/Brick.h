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
	bool CheckBallCollision( const Ball& ball ) const;
	void ExecuteBallCollision( Ball& ball );
	Vec2 GetCenter() const;
public:
	static constexpr float padding = 1.0f;
	RectF rect;
	Color c;
	bool destroyed = false;
};