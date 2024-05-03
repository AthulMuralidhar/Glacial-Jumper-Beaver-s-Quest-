#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth = 640;
    const int windowHeight = 640;
    InitWindow(windowWidth, windowHeight, "Glacial jumper");

    Texture2D backGround = LoadTexture("tileset/WinterTileset/png/BG/BG.png");
    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{1.f};


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the backGround
        DrawTextureEx(backGround, mapPosition, 0.0, mapScale, WHITE);


        EndDrawing();
    }

    UnloadTexture(backGround);
    CloseWindow();
}
