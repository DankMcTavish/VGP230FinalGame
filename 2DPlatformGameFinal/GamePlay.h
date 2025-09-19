#pragma once
#include "Character.h"
#include "Blocks.h"
#include <vector>


class GamePlay
{
public:
	GamePlay();

	void Main();
	void Start();
	void Draw();
	void Update();
	void ScoreUp();
	void UpdateScore();
	void GameOver();
	int GetScreenW() { return screenW; }
	int GetScreenH() { return screenH; }
	int GetScore() { return score; }

	void InitBlocks(int count, int screenWidth, int screenHeight);
	void DrawBlocks();


private:
	int screenW = 500;
	int screenH = 900;
	int score;
	float gravity = 0.1f;
	float lastScoreTime;
	bool isGameOver = false;
	std::vector<Blocks> blocks;
	Character player;

};