#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 vec, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);

private:
    Vector2 worldPosition;
    Texture2D texture;
    float propScale{4.f};
};