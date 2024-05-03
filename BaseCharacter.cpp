#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        .x = getScreenPosition().x,
        .y = getScreenPosition().y,
        .width = width * scale,
        .height = height * scale};
}

void BaseCharacter::undoMovement()
{
    worldPosition = lastFrameWorldPosition;
}

void BaseCharacter::tick(float dT)
{
    lastFrameWorldPosition = worldPosition;

    // update animation frame
    runningTime += dT;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        currentFrame++;

        if (currentFrame > maxFrames)
            currentFrame = 0;
    }

    // update movement
    if (Vector2Length(velocity) != 0.0)
    {
        // world position += direction
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(velocity), speed));

        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        // set sprite sheet based on character's movement
        currentTexture = runTexture;
    }
    else
    {
        currentTexture = idleTexture;
    }
    velocity = {}; // reset velocity as it is updated each frame (each tick)

    // draw character
    Rectangle source{
        .x = currentFrame * width,
        .y = 0.0,
        .width = rightLeft * width,
        .height = height,
    };

    Rectangle destination{
        .x = getScreenPosition().x,
        .y = getScreenPosition().y,
        .width = width * scale,
        .height = height * scale,
    };
    DrawTexturePro(currentTexture, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);
}