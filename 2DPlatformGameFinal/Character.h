#pragma once
#include <raylib.h>


class Character
{
public:
	
	Character(int screenW, int screenH, Vector2 size, Color color);


	void Draw();
	void Move(Vector2 direction);
	void Controls();
	void Update(int w, int y);
	Rectangle GetCollisionRect() const;
	Vector2 playerLocation;
	bool isOnBlock;
	bool isJumping;
	bool isFalling;
	Vector2 velocity;
	void LandOnBlock(float xy);
	Texture2D characterTexture; 

private:	
	Vector2 playerSize;
	Color playerColour;
	float speed;
	float gravity;
	float jumpForce = -15.0f;

};