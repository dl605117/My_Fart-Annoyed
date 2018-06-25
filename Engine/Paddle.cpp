#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
}

void Paddle::Draw(Graphics & gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect( rect, wingColor );
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect( rect, paddleColor );
}

void Paddle::Update(const Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
		pos.x -= speed * dt;
	else if (kbd.KeyIsPressed(VK_RIGHT))
		pos.x += speed * dt;
}

bool Paddle::DoBallCollision(Ball& ball)
{
	const RectF rect = GetRect();
	if (!onCoolDown)
	{
		if (GetRect().IsCollidingWith(ball.GetRect()))
		{
			if (std::signbit(ball.GetVelocity().x) == std::signbit((ball.GetPosition() - pos).x))
			{
				ball.ReboundY();
			}
			else if (ball.GetPosition().x >= rect.left && ball.GetPosition().x <= rect.right)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
			onCoolDown = true;
			return true;
		}
	}
	return false;
}

void Paddle::DoWallCollision(const RectF& wall)
{
	const RectF paddle = GetRect();
	if (paddle.left < wall.left)
		pos.x += wall.left - paddle.left;
	else if (paddle.right > wall.right)
		pos.x -= paddle.right - wall.right;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

void Paddle::ResetCoolDown()
{
	onCoolDown = false;
}