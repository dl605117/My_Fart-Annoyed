#pragma once
#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(const Vec2& pos, const Vec2& vel);
	void Draw(Graphics& gfx) const;
	void Update( float dt );
public:
	Vec2 pos;
	Vec2 vel;
};