#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPosition() { return worldPosition; };
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float dT);
    virtual Vector2 getScreenPosition() = 0; // a pure virtual function making this an abstract class
    // meaning, that this class cannot have an instance of its own
    bool getAlive() { return alive; };
    void setAive(bool isAlive){alive = isAlive;};

protected:
    Texture2D currentTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idleTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D runTexture{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPosition{}; // upper left corner of the world / window
    float speed{4.f};
    // 1 == facing right, -1 == facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    float updateTime{1.f / 12.f};
    int currentFrame{};
    int maxFrames{6};
    float width{};
    float height{};
    Vector2 lastFrameWorldPosition{};
    float scale = 4.f;
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif