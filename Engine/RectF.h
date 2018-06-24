#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF( float left, float top, float right, float bottom);
	RectF( const Vec2& topLeft, const Vec2& bottomRight );
	RectF(const Vec2& topLeft, float width, float height);
	bool IsCollidingWith( const RectF& rect ) const;
	static RectF FromCenter( const Vec2& rect, float halfWidth, float halfHeight);
	RectF GetExpanded(float padding ) const;
public:
	float left;
	float top;
	float right;
	float bottom;
};