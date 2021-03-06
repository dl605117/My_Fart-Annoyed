/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(300.0f, 300.0f), Vec2(-300.0f, -300.0f)),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	paddle(Vec2(400.0f, 500.0f), 50.0f, 15.0f),
	soundBall( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" )
{
	constexpr Color c[4] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };

	Vec2 topLeft( 40.0f, 40.0f);
	int countBricks = 0;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			bricks[countBricks] = Brick( RectF( topLeft + Vec2( j * brickWidth, i * brickHeight ), brickWidth, brickHeight), c[i] );
				countBricks++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();
	while ( elapsedTime > 0 )
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel( dt );
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	ball.Update(dt);
	
	paddle.Update( wnd.kbd, dt );
	paddle.DoWallCollision(walls);
	paddle.DoBallCollision( ball );

	bool collidedBefore = false;
	float currentDistanceSq;
	int currentBrickIndex;

	for (int i = 0; i < nBricks; i++) {
		if (bricks[i].CheckBallCollision(ball)) {
			float newDistanceSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
			if (collidedBefore && newDistanceSq < currentDistanceSq)
			{
				currentDistanceSq = newDistanceSq;
				currentBrickIndex = i;
			}
			else {
				collidedBefore = true;
				currentDistanceSq = newDistanceSq;
				currentBrickIndex = i;
			}
		}
	}
	
	if (collidedBefore)
	{
		paddle.ResetCooldown();
		bricks[currentBrickIndex].ExecuteBallCollision(ball);
		soundBrick.Play();
	}
		
	if (ball.DoWallCollision(walls))
	{
		paddle.ResetCooldown();
		soundBall.Play();
	}
}

void Game::ComposeFrame()
{
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for ( const Brick& brick : bricks)
		brick.Draw(gfx);
}
