#include "raylib.h"
#include "raymath.h"
#include <time.h>
#include <stdio.h>


void main() {
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Ray Space Shooter");

    Texture2D playerTexture = LoadTexture("../Assets/images/player.png");
    Vector2 playerPos = {(screenWidth/2)-playerTexture.width/2, ((screenHeight/4)*3)-playerTexture.height/2};
    Rectangle playerSrcRect = {0,0, playerTexture.width, playerTexture.height};
    Rectangle playerDestRect = {playerPos.x, playerPos.y,  playerTexture.width, playerTexture.height};
    // Vector2 playerDirectionVec = { 2, -2 };
    float playerSpeed = 100.f;

    Texture2D starTexture = LoadTexture("../Assets/images/star.png");
    SetRandomSeed((unsigned int)time(NULL));
    int starListPosX[20];
    for(int i=0; i<20;i++) {
        starListPosX[i] = GetRandomValue(0, screenWidth - starTexture.width);
    }
    int starListPosY[20];
    for(int i=0; i<20;i++) {
        starListPosY[i] = GetRandomValue(0, screenHeight - starTexture.height);
    }

    // SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // playerPos = Vector2Add(playerPos, Vector2Scale(playerDirectionVec, playerSpeed * GetFrameTime()));
        playerDestRect.x = GetMousePosition().x;
        playerDestRect.y = GetMousePosition().y;
        BeginDrawing();

            ClearBackground(DARKBLUE);

            for(int i = 0; i < 20; i++) {
                DrawTexture(starTexture, starListPosX[i], starListPosY[i], WHITE);
            }

            DrawTexturePro(playerTexture, playerSrcRect, playerDestRect, (Vector2){ playerTexture.width/2, playerTexture.height/2 }, 0.f, WHITE);


        EndDrawing();
    }

    UnloadTexture(playerTexture);
    UnloadTexture(starTexture);

    CloseWindow();
}