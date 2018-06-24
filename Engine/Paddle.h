#pragma once
#include "Ball.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& pos, float halfWidth, float halfHeight);
	void Draw( Graphics& gfx ) const;
	void Update( const Keyboard& kbd, float dt );
	bool DoBallCollision( Ball& ball ) const;
	void DoWallCollision( const RectF& wall );
	RectF GetRect() const;
private:
	float halfWidth;
	float halfHeight;
	static constexpr float speed = 300.0f;
	Color paddleColor = Colors::White;
	Vec2 pos;
	Vec2 vel;
};