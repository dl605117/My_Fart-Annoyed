#include "Brick.h"

Brick::Brick(const RectF & rect, Color c)
	:
	rect(rect),
	c(c)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if ( !destroyed )
		gfx.DrawRect( rect, c );
}

bool Brick::DoBallCollision(Ball & ball)
{
	if ( !destroyed && rect.IsCollidingWith(ball.GetRect()))
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;
}
