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
	gfx.DrawRect( rect, padColor);
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if (!onCooldown && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		const float ballPosX = ball.GetPosition().x;
		if (std::signbit(ball.GetVel().x) == std::signbit(ballPosX - pos.x))
		{
			ball.ReboundY();
		}
		else if (ballPosX >= pos.x - halfWidth && ballPosX <= pos.x + halfWidth)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX();
		}
		onCooldown = true;
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RectF & walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
		pos.x += walls.left - rect.left;
	else if (rect.right > walls.right)
		pos.x -= rect.right - walls.right;
}

void Paddle::Update(const Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
		pos.x -= speed * dt;
	else if (kbd.KeyIsPressed(VK_RIGHT))
		pos.x += speed * dt;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

void Paddle::ResetCooldown()
{
	onCooldown = false;
}