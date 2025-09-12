#include "GamePlay.h"
#include "Blocks.h"
#include "raylib.h"	
#include <iostream>
#include <vector>


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
}

void GamePlay::Start()
{
	score = 0;
	isGameOver = false;
	InitBlocks(9, screenW, screenH);
}


void GamePlay::InitBlocks(int count, int screenWidth, int screenHeight) 
{
	blocks.clear();
	for (int i = 0; i < count; i++) {
		float x = GetRandomValue(0, screenWidth - 60);
		float y = screenHeight - i * 150; // space vertically
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

#include "raymath.h" // Include raymath for vector operations

void GamePlay::Update()
{
    player.Controls();
    player.Update();

    ScoreUp();

    if (player.playerLocation.y > screenH)
    {
        isGameOver = true;
    }

    if (isGameOver)
    {
        // Game over logic
        GameOver();
    }

    for (int i = 0; i < blocks.size(); i++) 
    {
        // Convert Rectangle to BoundingBox for collision check
        BoundingBox playerBox = {
            Vector3{ player.GetCollisionRect().x, player.GetCollisionRect().y, 0 },
            Vector3{ player.GetCollisionRect().x + player.GetCollisionRect().width, player.GetCollisionRect().y + player.GetCollisionRect().height, 0 }
        };

        BoundingBox blockBox = {
            Vector3{ blocks[i].GetRect().x, blocks[i].GetRect().y, 0 },
            Vector3{ blocks[i].GetRect().x + blocks[i].GetRect().width, blocks[i].GetRect().y + blocks[i].GetRect().height, 0 }
        };

        if (CheckCollisionBoxes(playerBox, blockBox))
        {
            // Handle collision logic here
			player.playerLocation.y = blocks[i].GetRect().y - player.GetCollisionRect().height; // Position player on top of block
			player.velocity.y = 0; // Stop downward velocity
			player.isJumping = false; // Allow jumping again
        }
		else
		{
			player.isOnGround = false; // Not on ground if not colliding
		}

		// Move blocks downwards
		blocks[i].MoveDown(2.0f); // Adjust speed as necessary
		// Reposition block if it goes off-screen
		if (blocks[i].GetRect().y > screenH)
		{
			float x = GetRandomValue(0, screenW - 60);
			float y = -60; // Start above the screen
			blocks[i] = Blocks(x, y); // Reset block position
		}

		player.isOnGround = false;

    }
}

void GamePlay::ScoreUp()
{
	float lastScoreTime = 0.0f;
	float time = GetTime();

	if (!isGameOver)
	{
		if (time - lastScoreTime >= 1.0f) // Increase score every second
		{
			score++;
			lastScoreTime = time;
		}
	}

	if (isGameOver)
	{
		DrawText(TextFormat("Score: %d", score/10), 10, 10, 20, BLACK);
	}


		DrawText(TextFormat("Score: %d", score/10), 10, 10, 20, BLACK);
}

void GamePlay::GameOver()
{
	DrawText("Game Over!", screenW / 2 - 100, screenH / 2 - 50, 40, RED);
}
