#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF rect, Color c)
	:
	rect(rect),
	c(c)
{
}

void Brick::Draw( Graphics & gfx) const
{ 
	if (!destroyed)
		gfx.DrawRect( rect.GetExpanded( -padding ), c );
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !destroyed && rect.IsOverlappingWith( ball.GetRect() );
}

void Brick::ExecuteBallCollision( Ball& ball )
{
	const float ballPosX = ball.GetPosition().x;
	assert( CheckBallCollision( ball ) );
	if (std::signbit(ball.GetVel().x) == std::signbit(ballPosX - GetCenter().x))
	{
		ball.ReboundY();
	}
	else if (ballPosX >= rect.left && ballPosX <= rect.right)
	{
		ball.ReboundY();
	}
	else 
	{
		ball.ReboundX();
	}
	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return Vec2( (rect.left + rect.right) / 2.0f, (rect.top + rect.bottom) / 2.0f );
}