#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF & rect, Color c)
	:
	rect(rect),
	c(c),
	destroyed(false)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if ( !destroyed )
		gfx.DrawRect( rect.GetExpanded(-padding), c );
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !destroyed && rect.IsCollidingWith(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball & ball)
{
	assert( CheckBallCollision( ball ) );
	if (ball.GetPosition().x >= rect.left && ball.GetPosition().x <= rect.right)
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