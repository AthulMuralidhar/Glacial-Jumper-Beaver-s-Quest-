#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "tops");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{4.f};

    // init character
    Character knight{windowWidth, windowHeight};

    // init props
    Prop props[2]{
        {Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        {Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    // init  enemies
    // Enemy *enemies[]{
    //     new Enemy{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")},
    //     new Enemy{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")},
    // };

    // goblin.setTarget(&knight);

    // for (auto enemy : enemies)
    // {
    //     enemy->setTarget(&knight);
    // }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the map
        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        // render props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPosition());
        }

        if (!knight.getAlive())
        {
            DrawText("game over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string health = "health: ";
            health.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(health.c_str(), 55.f, 45.f, 40, RED);
        }

        // render knight
        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPosition().x < 0.f ||
            knight.getWorldPosition().y < 0.f ||
            knight.getWorldPosition().x + windowWidth > map.width * mapScale ||
            knight.getWorldPosition().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check for prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPosition()), knight.getCollisionRec()))
                knight.undoMovement();
        }



        EndDrawing();
    }

    UnloadTexture(map);
    // UnloadTexture(knightIdle);  // make destructor
    // UnloadTexture(knightRun);
    CloseWindow();
}
