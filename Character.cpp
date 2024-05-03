#include "Character.h"
#include "raymath.h"
#include <iostream>

Character::Character(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{
    // // character only
    width = static_cast<float>(currentTexture.width) / maxFrames;
    height = static_cast<float>(currentTexture.height);

    // screen position == knight position
    // screenPosition = {
    //     .x = windowWidth / 2.0f - scale * (0.5f * width), // centere the knight
    //     .y = windowHeight / 2.0f - scale * (0.5f * height),
    // };
}

Vector2 Character::getScreenPosition()
{
    return Vector2{
        .x = windowWidth / 2.0f - scale * (0.5f * width), // centere the knight
        .y = windowHeight / 2.0f - scale * (0.5f * height),
    };
}

void Character::tick(float dT)
{
    if (!getAlive())
        return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(dT);

    // draw sword
    Vector2 swordOrigin{};
    Vector2 swordOffset{};
    float rotation{};

    if (rightLeft > 0.f) // facing right
    {
        swordOrigin = {0.f, weapon.height * scale};
        swordOffset = {35.f, 55.f}; // trial and error
        weaponCollisionRec = {
            .x = getScreenPosition().x + swordOffset.x,
            // we have to subsctract the weapon height, cause the collision rec function takes the rectangle xy as its origin
            .y = getScreenPosition().y + swordOffset.y - weapon.height * scale,
            .width = weapon.width * scale,
            .height = weapon.height * scale,
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        // facing left
        swordOrigin = {weapon.width * scale, weapon.height * scale};
        swordOffset = {25.f, 55.f};
        weaponCollisionRec = {
            .x = getScreenPosition().x + swordOffset.x - weapon.width * scale,
            .y = getScreenPosition().y + swordOffset.y - weapon.height * scale,
            .width = weapon.width * scale,
            .height = weapon.height * scale,
        };
         rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    Rectangle src{
        .x = 0.f,
        .y = 0.f,
        .width = weapon.width * rightLeft,
        .height = static_cast<float>(weapon.height),
    };
    Rectangle dst{
        .x = getScreenPosition().x + swordOffset.x,
        .y = getScreenPosition().y + swordOffset.y,
        .width = weapon.width * scale,
        .height = weapon.height * scale,
    };
    DrawTexturePro(weapon, src, dst, swordOrigin, rotation, WHITE);

    // draw collision rec
    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}


void Character::takeDamage(float  damage) {
    health -= damage;
    if (health <= 0.f)
    {
        setAive(false);
    }
    
}