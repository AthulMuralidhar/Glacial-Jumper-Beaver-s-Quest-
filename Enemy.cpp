#include "Enemy.h"
#include "raymath.h"
#include <iostream>

// on enemy ai
// in general a vector from a source location to a destination location = position vector of destination - position vector of source

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex)
{
    width = currentTexture.width / maxFrames;
    height = currentTexture.height;
    currentTexture = idleTex;
    speed = 3.5f;
    worldPosition = pos;
    idleTexture = idleTex;
    runTexture = runTex;
}

Vector2 Enemy::getScreenPosition()
{
    return Vector2Subtract(worldPosition, target->getWorldPosition());
}

void Enemy::tick(float dT)
{
    if (!getAlive())
        return;
    // get toTarget vector
    velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());

    if (Vector2Length(velocity) < radius) velocity  = {};
    

    BaseCharacter::tick(dT);


    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec())) {
        target->takeDamage(damagePerSec*dT);
    }
    
}

void Enemy::setTarget(Character *character)
{
    target = character;
}
