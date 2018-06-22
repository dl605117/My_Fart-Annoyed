#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF( float left, float top, float right, float bottom );
	RectF( const Vec2& topLeft, const Vec2& bottomRight );
	RectF( const Vec2& topLeft, const float width, const float height);
	bool IsOverlappingWith( const RectF& rhs ) const;
public:
	float left;
	float top;
	float right;
	float bottom;
};