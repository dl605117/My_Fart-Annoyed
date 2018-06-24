#include "RectF.h"

RectF::RectF(float left, float top, float right, float bottom)
	:
	left(left),
	top(top),
	right(right),
	bottom(bottom)
{
}

RectF::RectF(const Vec2 & topLeft, const Vec2 & bottomRight)
	:
	RectF(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
{
}

RectF::RectF(const Vec2 & topLeft, float width, float height)
	:
	RectF(topLeft, Vec2(topLeft.x + width, topLeft.y + height))
{
}

bool RectF::IsCollidingWith(const RectF& rect) const
{
	return left <= rect.right &&
		top >= rect.bottom &&
		right <= rect.left &&
		bottom >= rect.top;
}

RectF RectF::FromCenter(const Vec2& rect, float halfWidth, float halfHeight)
{
	const Vec2 halfVector(halfWidth, halfHeight);
	return RectF( rect - halfVector, rect + halfVector);
}