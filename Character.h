#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int windowWidth, int windowHeight);
    virtual void tick(float dT) override;
    virtual Vector2 getScreenPosition() override;
    Rectangle getweaponCollisionRec() { return weaponCollisionRec; };
    void takeDamage(float damage);
    float getHealth() { return health; };

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif