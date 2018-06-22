#pragma once
#include "Ball.h"
#include "Vec2.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& pos, float halfWidth, float halfHeight );
	void Draw( Graphics & gfx ) const;
	bool DoBallCollision( Ball& ball ) const;
	void DoWallCollision( const RectF& walls );
	void Update( const Keyboard& kbd, float dt );
	RectF GetRect() const;
private:
	Color wingColor = Colors::Red;
	Color padColor = Colors::White;
	static constexpr float wingWidth = 5.0f;
	static constexpr float speed = 300.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
};