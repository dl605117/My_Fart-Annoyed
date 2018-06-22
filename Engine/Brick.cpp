#include "Brick.h"

Brick::Brick(const RectF rect)
	:
	rect(rect)
{
}

void Brick::Draw( Graphics & gfx) const
{ 
	gfx.DrawRect( rect, c );
}
