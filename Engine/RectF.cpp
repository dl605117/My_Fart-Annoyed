#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

RectF::RectF(const Vec2 & topLeft, const Vec2 & bottomRight)
	:
	RectF( topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2 & topLeft, const float width, const float height)
	:
	RectF( topLeft, topLeft + Vec2( width, height ))
{
}

bool RectF::IsOverlappingWith(const RectF & rhs) const
{
	return left <= rhs.right &&
		right >= rhs.left &&
		top <= rhs.bottom &&
		bottom >= rhs.top;
}

RectF RectF::FromCenter(const Vec2 & center, float halfWidth, float halfHeight)
{
	const Vec2 diff(halfWidth, halfHeight);
	return RectF(center - diff, center + diff);
}