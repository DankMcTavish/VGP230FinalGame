#include "Character.h"

Character::Character(int screenW, int screenH, Vector2 startPos, Color color)
{
    playerLocation = startPos;
    playerSize = { 40.0f, 40.0f }; 
    velocity = { 0.0f, 0.0f };
    jumpForce = -15.0f; 
    isJumping = false;
    isOnBlock = false;
    playerColour = color;
}

void Character::Draw()
{
    Rectangle playerRect = { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
    DrawRectangleRounded(playerRect, 0.2f, 0, playerColour); 
    DrawTexture(characterTexture, playerLocation.x, playerLocation.y,WHITE );
}

void Character::Update(int screenW, int screenH)
{
    // Only apply gravity if not on a block
    if (!isOnBlock && isJumping)
    {
        velocity.y += 0.5f; // gravity acceleration
        playerLocation.y += velocity.y;
    }
    else if (!isOnBlock && !isJumping)
    {
        // Player is falling but not from a jump (fell off a block)
        isJumping = true; 
        velocity.y = 0.0f; 
    }
    else if (isOnBlock)
    {
        playerLocation.y += velocity.y; 
    }

    if (playerLocation.x < 0) playerLocation.x = 0;
    if (playerLocation.x + playerSize.x > screenW) playerLocation.x = screenW - playerSize.x;
}

void Character::Controls()
{
    if (IsKeyDown(KEY_RIGHT)) playerLocation.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))  playerLocation.x -= 5.0f;

    if (IsKeyPressed(KEY_SPACE) && isOnBlock)
    {
        isJumping = true;
        isOnBlock = false;
        velocity.y = jumpForce; 
    }
}

Rectangle Character::GetCollisionRect() const
{
    return { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
}

void Character::LandOnBlock(float blockY)
{
    playerLocation.y = blockY - playerSize.y;
    isJumping = false;
    isOnBlock = true;
    velocity.y = 0.0f; 
}