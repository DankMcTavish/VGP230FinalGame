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
    player.Controls();
    player.Update();
    ScoreUp();

	player.isOnBlock = false;

    if (player.playerLocation.y > screenH)
    {
        isGameOver = true;
    }

    if (isGameOver)
    {
        GameOver();
    }

	
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].MoveDown(blocks[i].blockSpeed);
		if (blocks[i].position.y > screenH) 
		{
			blocks[i].position.y = 0;
			blocks[i].position.x = GetRandomValue(0, screenW - blocks[i].width);
		}
		if (CheckCollisionRecs(player.GetCollisionRect(), blocks[i].GetRect())) 
		{
		}

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
	DrawText(TextFormat("Score: %d", score/10), 10, 10, 20, BLACK);
}

void GamePlay::GameOver()
{
	DrawText("Game Over!", screenW / 2 - 100, screenH / 2 - 50, 40, RED);
}
