#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    virtual void tick(float dT) override;
    void setTarget(Character *character);
    virtual Vector2 getScreenPosition() override;

private:
    Character *target{};
    float damagePerSec{10.f};
    float radius{25.f};
};