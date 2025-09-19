#include "GamePlay.h"
#include "Blocks.h"
#include "raylib.h"	
#include <iostream>
#include <vector>
#include "raymath.h"

GamePlay::GamePlay()
	: player(screenW, screenH, { 50.0f, 50.0f }, RED)
{
}

void GamePlay::Main()
{
	Start();
	InitWindow(screenW, screenH, "Climber");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		Update();
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Draw();
		EndDrawing();
	}
	CloseWindow();
}

void GamePlay::Start()
{
	score = 0;
	isGameOver = false;
	fallSpeed = 1.0f; 
	InitBlocks(numOfBlocks, screenW, screenH);

	player.playerLocation = { 50.0f, 50.0f }; 
	player.velocity = { 0.0f, 0.0f }; 
	player.isOnBlock = false;
}

void GamePlay::InitBlocks(int count, int screenWidth, int screenHeight)
{
	blocks.clear();
	for (int i = 0; i < count; i++) {
		float x = GetRandomValue(0, screenWidth - 60);
		float y = screenHeight - i * 100 + GetRandomValue(-20, 20);		
		blocks.push_back(Blocks(x, y));
	}
}

void GamePlay::DrawBlocks()
{
	for (auto& block : blocks)
	{
		block.Draw();
	}
}

void GamePlay::Draw()
{
	player.Draw();
	DrawBlocks();
}

void GamePlay::Update()
{
	if (!isGameOver)
	{
		player.Controls();

		CheckCollisions();

		player.Update(screenW, screenH);
	}
	ScoreUp();

	if (player.playerLocation.y > screenH)
	{
		isGameOver = true;
	}

	if (isGameOver)
	{
		GameOver();
		return;
	}

	// Move blocks down
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].MoveDown(fallSpeed);
		if (blocks[i].position.y > screenH)
		{
			blocks[i].position.y = -blocks[i].height;
			blocks[i].position.x = GetRandomValue(0, screenW - blocks[i].width);
		}
	}
}

void GamePlay::CheckCollisions()
{
	Rectangle playerRect = player.GetCollisionRect();

	float nextPlayerY = playerRect.y;
	if (!player.isOnBlock && player.isJumping)
	{
		nextPlayerY = playerRect.y + player.velocity.y + 0.5f; 
	}
	else if (player.isOnBlock)
	{
		nextPlayerY = playerRect.y + fallSpeed;
	}

	Rectangle nextPlayerRect = { playerRect.x, nextPlayerY, playerRect.width, playerRect.height };

	bool wasOnBlock = player.isOnBlock;

	bool foundBlock = false;

	for (int i = 0; i < blocks.size(); i++)
	{
		Rectangle blockRect = blocks[i].GetRect();

		bool isFalling = player.velocity.y >= 0;

		bool willCollide = false;

		bool currentlyInside = CheckCollisionRecs(playerRect, blockRect);

		bool willBeInside = CheckCollisionRecs(nextPlayerRect, blockRect);

		bool approachingFromAbove = (playerRect.y + playerRect.height <= blockRect.y + 2) &&
			(nextPlayerRect.y + nextPlayerRect.height >= blockRect.y - 2);

		bool hasHorizontalOverlap =
			(playerRect.x + playerRect.width > blockRect.x + 8) &&
			(playerRect.x < blockRect.x + blockRect.width - 8);

		willCollide = isFalling && approachingFromAbove && hasHorizontalOverlap && (willBeInside || currentlyInside);

		if (willCollide)
		{
			player.playerLocation.y = blockRect.y - playerRect.height;

			player.isOnBlock = true;
			player.isJumping = false;
			player.velocity.y = fallSpeed; 

			foundBlock = true;
			break; 
		}
	}

	if (!foundBlock && wasOnBlock)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			Rectangle blockRect = blocks[i].GetRect();

			bool stillOnBlock =
				(abs((playerRect.y + playerRect.height) - blockRect.y) <= 3) &&
				(playerRect.x + playerRect.width > blockRect.x + 5) &&
				(playerRect.x < blockRect.x + blockRect.width - 5);

			if (stillOnBlock)
			{
				foundBlock = true;
				player.isOnBlock = true;
				player.velocity.y = fallSpeed;
				break;
			}
		}
		if (!foundBlock)
		{
			player.isOnBlock = false;
			player.isJumping = true;
			player.velocity.y = 1.0f; 
		}
	}
}

void GamePlay::ResetBlocks(Blocks platform)
{
	platform.position.y = 0;
	platform.position.x = GetRandomValue(0, screenW - platform.width);
}

void GamePlay::ScoreUp()
{
	static float lastScoreTime = 0.0f;
	float currentTime = GetTime();
	static int lastScoreCheckPoint = 0;

	if (score >= lastScoreCheckPoint + 100)
	{
		fallSpeed++;
		lastScoreCheckPoint = score;
	}

	if (!isGameOver)
	{
		if (currentTime - lastScoreTime >= 0.1f) 
		{
			score++;
			lastScoreTime = currentTime;
		}
	}

	DrawText(TextFormat("Score: %d", score / 10), 50, 50, 50, BLACK);
	DrawText(TextFormat("Level: %d", fallSpeed), 60, 90, 50, BLACK);
}

void GamePlay::RestartGame()
{
	score = 0;
	isGameOver = false;
	fallSpeed = 1.0f; 

	player.playerLocation = { 50.0f, 50.0f }; 
	player.velocity = { 0.0f, 0.0f }; 
	player.isOnBlock = false;

	InitBlocks(numOfBlocks, screenW, screenH);

	static bool resetStatics = true;
	if (resetStatics) {
		GetTime(); 
		resetStatics = false;
	}

}

void GamePlay::GameOver()
{
	// Draw game over screen
	DrawText("Game Over!", screenW / 2 - 100, screenH / 2 - 50, 40, RED);
	DrawText(TextFormat("Final Score: %d", score / 10), screenW / 2 - 80, screenH / 2, 30, BLACK);
	DrawText("Press R to Restart", screenW / 2 - 90, screenH / 2 + 40, 20, DARKGRAY);
	DrawText("Press ESC to Quit", screenW / 2 - 85, screenH / 2 + 65, 20, DARKGRAY);

	// Handle restart input
	if (IsKeyPressed(KEY_R))
	{
		RestartGame();
	}
}