#include "Character.h"

Character::Character(int screenW, int screenH, Vector2 startPos, Color color)
{
    playerLocation = startPos;
    playerSize = { 40.0f, 40.0f }; // Set default player size
    velocity = { 0.0f, 0.0f };
    jumpForce = -15.0f; // Negative for upward jump
    isJumping = false;
    isOnBlock = false;
    playerColour = color;
}

void Character::Draw()
{
    Rectangle playerRect = { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
    DrawRectangleRounded(playerRect, 0.2f, 0, playerColour); // Use playerColor instead of RED
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
        isJumping = true; // Start falling
        velocity.y = 0.0f; // Start with zero velocity when starting to fall
    }
    else if (isOnBlock)
    {
        // Player is on a block - the GameMode will handle the Y movement
        // Don't modify velocity.y here, let GameMode control it
        playerLocation.y += velocity.y; // Apply the velocity set by GameMode
    }

    // Keep player within screen bounds horizontally
    if (playerLocation.x < 0) playerLocation.x = 0;
    if (playerLocation.x + playerSize.x > screenW) playerLocation.x = screenW - playerSize.x;
}

void Character::Controls()
{
    if (IsKeyDown(KEY_RIGHT)) playerLocation.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))  playerLocation.x -= 5.0f;

    // Only allow jumping if on a block (not while falling)
    if (IsKeyPressed(KEY_SPACE) && isOnBlock)
    {
        isJumping = true;
        isOnBlock = false;
        velocity.y = jumpForce; // Your jump strength (should be negative, like -10.0f)
    }
}

Rectangle Character::GetCollisionRect() const
{
    return { playerLocation.x, playerLocation.y, playerSize.x, playerSize.y };
}

// Add this method to reset falling state when landing on block
void Character::LandOnBlock(float blockY)
{
    playerLocation.y = blockY - playerSize.y;
    isJumping = false;
    isOnBlock = true;
    velocity.y = 0.0f; // Will be set by GameMode to match block speed
}