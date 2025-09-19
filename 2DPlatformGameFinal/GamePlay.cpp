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
	fallSpeed = 1.0f; // Reset fall speed to initial value
	InitBlocks(9, screenW, screenH);

	// Reset player to starting position and state
	player.playerLocation = { 50.0f, 50.0f }; // Reset to starting position
	player.velocity = { 0.0f, 0.0f }; // Reset velocity
	player.isOnBlock = false;
}

void GamePlay::InitBlocks(int count, int screenWidth, int screenHeight)
{
	blocks.clear();
	for (int i = 0; i < count; i++) {
		float x = GetRandomValue(0, screenWidth - 60);
		float y = screenHeight - i * 150;
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

		// Check collision BEFORE updating player position
		CheckCollisions();

		// Now update player
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
	// Get current player rectangle
	Rectangle playerRect = player.GetCollisionRect();

	// Calculate where player will be next frame
	float nextPlayerY = playerRect.y;
	if (!player.isOnBlock && player.isJumping)
	{
		nextPlayerY = playerRect.y + player.velocity.y + 0.5f; // Include gravity
	}
	else if (player.isOnBlock)
	{
		nextPlayerY = playerRect.y + fallSpeed;
	}

	// Create next frame's player rectangle
	Rectangle nextPlayerRect = { playerRect.x, nextPlayerY, playerRect.width, playerRect.height };

	// Store previous state
	bool wasOnBlock = player.isOnBlock;

	// Assume player is not on any block initially
	bool foundBlock = false;

	// Check collision with all blocks
	for (int i = 0; i < blocks.size(); i++)
	{
		Rectangle blockRect = blocks[i].GetRect();

		// Check if player is falling
		bool isFalling = player.velocity.y >= 0;

		// More robust collision detection
		bool willCollide = false;

		// Current frame collision check
		bool currentlyInside = CheckCollisionRecs(playerRect, blockRect);

		// Next frame collision check
		bool willBeInside = CheckCollisionRecs(nextPlayerRect, blockRect);

		// Check if player is approaching from above
		bool approachingFromAbove = (playerRect.y + playerRect.height <= blockRect.y + 2) &&
			(nextPlayerRect.y + nextPlayerRect.height >= blockRect.y - 2);

		// Check horizontal overlap (stricter requirements)
		bool hasHorizontalOverlap =
			(playerRect.x + playerRect.width > blockRect.x + 8) &&
			(playerRect.x < blockRect.x + blockRect.width - 8);

		// Determine if collision should happen
		willCollide = isFalling && approachingFromAbove && hasHorizontalOverlap && (willBeInside || currentlyInside);

		if (willCollide)
		{
			// Snap player to exact top of block
			player.playerLocation.y = blockRect.y - playerRect.height;

			// Set player state
			player.isOnBlock = true;
			player.isJumping = false;
			player.velocity.y = fallSpeed; // Move down with block

			foundBlock = true;
			std::cout << "Player landed on block " << i << " at Y: " << blockRect.y << std::endl;
			break; // Only one block at a time
		}
	}

	// If no block was found but player was on a block last frame
	if (!foundBlock && wasOnBlock)
	{
		// Double-check: is player still on any block?
		for (int i = 0; i < blocks.size(); i++)
		{
			Rectangle blockRect = blocks[i].GetRect();

			// Check if player is still standing on this block
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

		// If truly no block, start falling
		if (!foundBlock)
		{
			player.isOnBlock = false;
			player.isJumping = true;
			player.velocity.y = 1.0f; // Small initial fall velocity
			std::cout << "Player fell off all blocks!" << std::endl;
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
		if (currentTime - lastScoreTime >= 0.1f) // Increase score every 0.1 seconds (10 times per second)
		{
			score++;
			lastScoreTime = currentTime;
		}
	}

	DrawText(TextFormat("Score: %d", score / 10), 10, 10, 20, BLACK);
}

void GamePlay::RestartGame()
{
	// Reset all game variables to their initial state
	score = 0;
	isGameOver = false;
	fallSpeed = 1.0f; // Reset to initial fall speed

	// Reset player position and state
	player.playerLocation = { 50.0f, 50.0f }; // Reset to starting position
	player.velocity = { 0.0f, 0.0f }; // Reset velocity
	player.isOnBlock = false;

	// Reinitialize blocks
	InitBlocks(9, screenW, screenH);

	// Reset static variables in ScoreUp - this is crucial!
	static bool resetStatics = true;
	if (resetStatics) {
		// Force reset of static variables by calling GetTime() to sync
		GetTime(); // This helps reset the time reference
		resetStatics = false;
	}

	std::cout << "Game Restarted!" << std::endl; // Debug message
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