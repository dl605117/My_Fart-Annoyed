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
		gfx.DrawRect( rect.GetExpanded(-padding), c );
}

bool Brick::DoBallCollision(Ball & ball)
{
	if (!destroyed && rect.IsCollidingWith(ball.GetRect()))
	{
		if (ball.GetPosition().x > rect.left && ball.GetPosition().x < rect.right)
			ball.ReboundY();
		else
			ball.ReboundX();
		destroyed = true;
		return true;
	}
	return false;
}
