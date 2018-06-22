#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball( const Vec2& pos, const Vec2& vel );
	void Draw( Graphics& gfx) const;
public:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};