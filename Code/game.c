#include "raylib.h"
#include "raymath.h"
#include <time.h>
#include <stdio.h>

struct Sprite {
    Texture2D spriteTexture;
    Rectangle SrcRect;
    Rectangle DestRect;
    Vector2 origin;
}typedef Sprite;


void SpriteSetup(Sprite* sprite);

Sprite PlayerInit();

Vector2 PlayerControls(Vector2 playerDirectionVec, Vector2 playerPos, float playerSpeed, Sprite* player);


void StarsInit(int screenWidth, int screenHeight, Sprite* starSprite, int starPosList[2][20]);


void main() {
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Ray Space Shooter");

    Sprite player = PlayerInit();
    Vector2 playerPos = {(screenWidth/2)-player.spriteTexture.width/2, ((screenHeight/4)*3)-player.spriteTexture.height/2};
    player.DestRect.x = playerPos.x; player.DestRect.y = playerPos.y; 
    Vector2 playerDirectionVec = { 0, 0 };
    float playerSpeed = 500.f;
    
    Sprite starSprite;
    int starPosList[2][20] = { 0 };
    StarsInit(screenWidth, screenHeight, &starSprite, starPosList);


    // SetTargetFPS(60);

    while (!WindowShouldClose()) {

        playerPos = PlayerControls(playerDirectionVec, playerPos, playerSpeed, &player);

        
        BeginDrawing();

            ClearBackground(DARKBLUE);

            for(int i = 0; i < 20; i++) {
                DrawTexture(starSprite.spriteTexture, starPosList[0][i], starPosList[1][i], WHITE);
            }

            DrawTexturePro(player.spriteTexture, player.SrcRect, player.DestRect, player.origin, 0.f, WHITE);


        EndDrawing();
    }

    UnloadTexture(player.spriteTexture);
    UnloadTexture(starSprite.spriteTexture);

    CloseWindow();
}



void SpriteSetup(Sprite* sprite) {
    Rectangle srcRect = {0, 0, sprite->spriteTexture.width, sprite->spriteTexture.height};
    Rectangle destRect = {0, 0,  sprite->spriteTexture.width, sprite->spriteTexture.height};
    Vector2 origin = {sprite->spriteTexture.width/2, sprite->spriteTexture.height/2};
    
    sprite->DestRect = destRect;
    sprite->SrcRect = srcRect;
    sprite->origin = origin;
}


Sprite PlayerInit() {
    Sprite playerSprite;

    playerSprite.spriteTexture = LoadTexture("../Assets/images/player.png");
    SpriteSetup(&playerSprite);

    return playerSprite;
}

Vector2 PlayerControls(Vector2 playerDirectionVec, Vector2 playerPos, float playerSpeed, Sprite* player) {
    playerDirectionVec.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    playerDirectionVec.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
    playerDirectionVec = Vector2Normalize(playerDirectionVec);

    playerPos = Vector2Add(playerPos, Vector2Scale(playerDirectionVec, playerSpeed * GetFrameTime()));
    player->DestRect.x = playerPos.x;
    player->DestRect.y = playerPos.y;

    return playerPos;
}


void StarsInit(int screenWidth, int screenHeight, Sprite* starSprite, int starPosList[2][20]) {

    starSprite->spriteTexture = LoadTexture("../Assets/images/star.png");
    SpriteSetup(starSprite);

    SetRandomSeed((unsigned int)time(NULL));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0)
                starPosList[i][j] = GetRandomValue(0, screenWidth - starSprite->spriteTexture.width);
            else if (i == 1)
                starPosList[i][j] = GetRandomValue(0, screenHeight - starSprite->spriteTexture.height);
        }
    }
}