#include "Character.h"


Character::Character(int screenW, int screenH, Vector2 size, Color color)
    : playerSize(size),
    playerColour(color),
    velocity{ 0.0f, 0.0f }
{
    playerLocation = 
    {
        (float)screenW / 2 - playerSize.x,
		(float)screenH - playerSize.y - 200.0f
    };
}


void Character::Draw() 
{
	Rectangle playerRect = { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
	DrawRectangleRounded(playerRect, 0.2f, 0, RED);
}

void Character::Move(Vector2 direction) 
{
    playerLocation.x += direction.x;
    playerLocation.y += direction.y;

    if (isJumping)
    {
	    velocity.y += 5.0f;
	    playerLocation.y += velocity.y;
    }
}

void Character::Update() 
{
    if (isJumping) 
    {
        velocity.y += 0.5f; // gravity acceleration
        playerLocation.y += velocity.y;
    }

    if (isOnBlock)
    {
        isJumping = false;
        velocity.y = 0.0f;
	}
}

void Character::Controls() 
{
    if (IsKeyDown(KEY_RIGHT)) playerLocation.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))  playerLocation.x -= 5.0f;
    if (IsKeyPressed(KEY_SPACE) && !isJumping)
    {
      isJumping = true;
      isOnBlock = false;
      velocity.y = jumpForce; // Your jump strength
    }
}

Rectangle Character::GetCollisionRect() const
{
    return { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
}
