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
	ft(),
	ball(Vec2(300.0f, 300.0f), Vec2(-300.0f, -300.0f)),
	wall(0.0f, 0.0f, float(Graphics::ScreenWidth), float(Graphics::ScreenHeight)),
	paddle(Vec2(400.0f, 500.0f), 50.0f, 15.0f),
	soundBall( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav")
{
	int brickCounter = 0;
	const Vec2 topLeft( 40.0f, 40.0f );
	const Color c[4] = {Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan};
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			bricks[brickCounter] = Brick( RectF(topLeft + Vec2(j * brickWidth, i * brickHeight), brickWidth, brickHeight), c[i]);
			brickCounter++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	ball.Update( dt );
	paddle.Update( wnd.kbd, dt );
	paddle.DoBallCollision( ball );
	paddle.DoWallCollision( wall );

	bool collidedBefore = false;
	float currentBallDistanceSq;
	int brickIndex;
	for ( int i = 0; i < nBricks; i++ )
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			float newBallDistanceSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
			if (collidedBefore)
			{
				if (newBallDistanceSq < currentBallDistanceSq)
				{
					currentBallDistanceSq = newBallDistanceSq;
					brickIndex = i;
				}
			}
			else
			{
				currentBallDistanceSq = newBallDistanceSq;
				collidedBefore = true;
				brickIndex = i;
			}
		}
	}

	if (collidedBefore)
	{
		bricks[brickIndex].ExecuteBallCollision(ball);
		soundBrick.Play();
	}

	if (ball.DoWallCollision(wall))
		soundBall.Play();
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	for (Brick& brick : bricks)
		brick.Draw(gfx);
	paddle.Draw(gfx);
}
