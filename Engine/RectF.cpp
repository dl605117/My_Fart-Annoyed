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
{
	RectF( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

RectF::RectF(const Vec2 & topLeft, const float width, const float height)
{
	RectF( topLeft, topLeft + Vec2( width, height ));
}

bool RectF::IsOverlappingWith(const RectF & rhs) const
{
	return left <= rhs.right &&
		right >= rhs.left &&
		top <= rhs.bottom &&
		bottom >= rhs.top;
}
