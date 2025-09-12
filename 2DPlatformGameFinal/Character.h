#pragma once
#include <raylib.h>


class Character
{
public:
	
	Character(int screenW, int screenH, Vector2 size, Color color);


	void Draw();
	void Move(Vector2 direction);
	void Controls();
	void Update();
	Rectangle GetCollisionRect() const;
	Vector2 playerLocation;
	bool isOnGround;
	bool isJumping;
	Vector2 velocity;

private:	
	Vector2 playerSize;
	Color playerColour;
	float speed;
	float gravity;
	float jumpForce = -15.0f;

};