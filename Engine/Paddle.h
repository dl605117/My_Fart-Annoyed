#pragma once
#include "Ball.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& pos, float halfWidth, float halfHeight);
	void Draw( Graphics& gfx ) const;
	void Update( const Keyboard& kbd, float dt );
	bool DoBallCollision( Ball& ball );
	void DoWallCollision( const RectF& wall );
	RectF GetRect() const;
	void ResetCoolDown();
private:
	float halfWidth;
	float halfHeight;
	static constexpr float speed = 300.0f;
	static constexpr float wingWidth = 5.0f;
	Color paddleColor = Colors::White;
	Color wingColor = Colors::Red;
	Vec2 pos;
	Vec2 vel;
	bool onCoolDown = false;
};