#pragma once
#include <vector>
#include "raylib.h"


class Blocks
{
public:
    Vector2 position;
    int width = 60;
    int height = 20;
    Color color = BLACK;
	float blockSpeed = 1.0f;



    Blocks(float x, float y)
        : position{ x, y } 
    {
    }

    void Draw() 
    {
        DrawRectangle((int)position.x, (int)position.y, width, height, color);
    }

    Rectangle GetRect() const 
    {
        return Rectangle{ position.x, position.y, (float)width, (float)height };
	}

    void MoveDown(float distance) 
    {
        position.y += distance;
	}
};