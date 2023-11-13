/**
 * @file arkanoid.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/raysan5/raylib-games/blob/master/classics/src/arkanoid.c
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../../hal/hal.h"
#include "../raylib/raylib.h"


namespace ARKANOID
{
    /*******************************************************************************************
    *
    *   raylib - classic game: arkanoid
    *
    *   Sample game developed by Marc Palau and Ramon Santamaria
    *
    *   This game has been created using raylib v1.3 (www.raylib.com)
    *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
    *
    *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
    *
    ********************************************************************************************/

    // #include "raylib.h"

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <math.h>

    #if defined(PLATFORM_WEB)
        #include <emscripten/emscripten.h>
    #endif

    //----------------------------------------------------------------------------------
    // Some Defines
    //----------------------------------------------------------------------------------
    #define PLAYER_MAX_LIFE         5
    #define LINES_OF_BRICKS         5
    #define BRICKS_PER_LINE         20
    #define BRICK_HEIGHT            10
    #define BALL_RADIUS             5
    #define BRICK_INIT_Y_OFFSET     BRICK_HEIGHT * 2
    #define PLAYER_WIDTH            BALL_RADIUS * 6
    #define PLAYER_HEIGHT           BALL_RADIUS
    #define PLAYER_SPEED            5

    //----------------------------------------------------------------------------------
    // Types and Structures Definition
    //----------------------------------------------------------------------------------
    typedef struct Player {
        Vector2 position;
        Vector2 size;
        int life;
    } Player;

    typedef struct Ball {
        Vector2 position;
        Vector2 speed;
        int radius;
        bool active;
    } Ball;

    typedef struct Brick {
        Vector2 position;
        bool active;
    } Brick;

    //------------------------------------------------------------------------------------
    // Global Variables Declaration
    //------------------------------------------------------------------------------------
    static const int screenWidth = 240;
    static const int screenHeight = 240;

    static bool gameOver = false;
    static bool pause = false;

    static Player player = { 0 };
    static Ball ball = { 0 };
    static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] = { 0 };
    static Vector2 brickSize = { 0 };

    //------------------------------------------------------------------------------------
    // Module Functions Declaration (local)
    //------------------------------------------------------------------------------------
    static void InitGame(void);         // Initialize game
    static void UpdateGame(void);       // Update game (one frame)
    static void DrawGame(void);         // Draw game (one frame)
    static void UnloadGame(void);       // Unload game
    static void UpdateDrawFrame(void);  // Update and Draw (one frame)
    static void CollisionCallback(void);

    //------------------------------------------------------------------------------------
    // Program main entry point
    //------------------------------------------------------------------------------------
    int main(void)
    {
        // Initialization (Note windowTitle is unused on Android)
        //---------------------------------------------------------
        InitWindow(screenWidth, screenHeight, "classic game: arkanoid");

        InitGame();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);
        //--------------------------------------------------------------------------------------

        auto update_count = HAL::Millis();

        // Main game loop
        // while (!WindowShouldClose())    // Detect window close button or ESC key
        while (1)
        {
            // // Update and Draw
            // //----------------------------------------------------------------------------------
            // UpdateDrawFrame();
            // //----------------------------------------------------------------------------------


            if (HAL::Millis() - update_count > 20)
            {
                UpdateDrawFrame();
                if (WindowShouldClose())
                    break;

                update_count = HAL::Millis();
            }


        }
    #endif
        // De-Initialization
        //--------------------------------------------------------------------------------------
        UnloadGame();         // Unload loaded data (textures, sounds, models...)

        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

        return 0;
    }

    //------------------------------------------------------------------------------------
    // Module Functions Definitions (local)
    //------------------------------------------------------------------------------------

    // Initialize game variables
    void InitGame(void)
    {
        brickSize = (Vector2){ static_cast<float>(GetScreenWidth()) / BRICKS_PER_LINE, BRICK_HEIGHT };

        // Initialize player
        player.position = (Vector2){ screenWidth/2, screenHeight*8/9 };
        player.size = (Vector2){ PLAYER_WIDTH, PLAYER_HEIGHT };
        player.life = PLAYER_MAX_LIFE;

        // Initialize ball
        ball.position = (Vector2){ screenWidth/2, player.position.y };
        ball.speed = (Vector2){ 0, 0 };
        ball.radius = BALL_RADIUS;
        ball.active = false;

        // Initialize bricks
        int initialDownPosition = BRICK_INIT_Y_OFFSET;

        for (int i = 0; i < LINES_OF_BRICKS; i++)
        {
            for (int j = 0; j < BRICKS_PER_LINE; j++)
            {
                brick[i][j].position = (Vector2){ j*brickSize.x + brickSize.x/2, i*brickSize.y + initialDownPosition };
                brick[i][j].active = true;
            }
        }
    }

    // Update game (one frame)
    void UpdateGame(void)
    {
        if (!gameOver)
        {
            // if (IsKeyPressed('P')) pause = !pause;
            if (HAL::GetButton(GAMEPAD::BTN_START))
                pause = !pause;

            if (!pause)
            {
                // Player movement logic
                // if (IsKeyDown(KEY_LEFT)) player.position.x -= 5;
                if (HAL::GetButton(GAMEPAD::BTN_LEFT))
                    player.position.x -= PLAYER_SPEED;

                if ((player.position.x - player.size.x/2) <= 0) player.position.x = player.size.x/2;

                // if (IsKeyDown(KEY_RIGHT)) player.position.x += 5;
                if (HAL::GetButton(GAMEPAD::BTN_RIGHT))
                    player.position.x += PLAYER_SPEED;

                if ((player.position.x + player.size.x/2) >= screenWidth) player.position.x = screenWidth - player.size.x/2;

                
                


                // Ball launching logic
                if (!ball.active)
                {
                    // if (IsKeyPressed(KEY_SPACE))
                    if (HAL::GetButton(GAMEPAD::BTN_A))
                    {
                        ball.active = true;
                        ball.speed = (Vector2){ 0, -5 };
                    }
                }

                // Ball movement logic
                if (ball.active)
                {
                    ball.position.x += ball.speed.x;
                    ball.position.y += ball.speed.y;
                }
                else
                {
                    ball.position = (Vector2){ player.position.x, player.position.y - BRICK_HEIGHT };
                }

                // Collision logic: ball vs walls
                if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0))
                {
                    ball.speed.x *= -1;
                    CollisionCallback();
                } 
                if ((ball.position.y - ball.radius) <= 0) 
                {
                    ball.speed.y *= -1;
                    CollisionCallback();
                }
                if ((ball.position.y + ball.radius) >= screenHeight)
                {
                    ball.speed = (Vector2){ 0, 0 };
                    ball.active = false;

                    player.life--;
                    CollisionCallback();
                }

                // Collision logic: ball vs player
                if (CheckCollisionCircleRec(ball.position, ball.radius,
                    (Rectangle){ player.position.x - player.size.x/2, player.position.y - player.size.y/2, player.size.x, player.size.y}))
                {
                    if (ball.speed.y > 0)
                    {
                        ball.speed.y *= -1;
                        ball.speed.x = (ball.position.x - player.position.x)/(player.size.x/2)*5;
                    }

                    CollisionCallback();
                }

                // Collision logic: ball vs bricks
                for (int i = 0; i < LINES_OF_BRICKS; i++)
                {
                    for (int j = 0; j < BRICKS_PER_LINE; j++)
                    {
                        if (brick[i][j].active)
                        {
                            // Hit below
                            if (((ball.position.y - ball.radius) <= (brick[i][j].position.y + brickSize.y/2)) &&
                                ((ball.position.y - ball.radius) > (brick[i][j].position.y + brickSize.y/2 + ball.speed.y)) &&
                                ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x/2 + ball.radius*2/3)) && (ball.speed.y < 0))
                            {
                                brick[i][j].active = false;
                                ball.speed.y *= -1;
                            }
                            // Hit above
                            else if (((ball.position.y + ball.radius) >= (brick[i][j].position.y - brickSize.y/2)) &&
                                    ((ball.position.y + ball.radius) < (brick[i][j].position.y - brickSize.y/2 + ball.speed.y)) &&
                                    ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x/2 + ball.radius*2/3)) && (ball.speed.y > 0))
                            {
                                brick[i][j].active = false;
                                ball.speed.y *= -1;
                            }
                            // Hit left
                            else if (((ball.position.x + ball.radius) >= (brick[i][j].position.x - brickSize.x/2)) &&
                                    ((ball.position.x + ball.radius) < (brick[i][j].position.x - brickSize.x/2 + ball.speed.x)) &&
                                    ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y/2 + ball.radius*2/3)) && (ball.speed.x > 0))
                            {
                                brick[i][j].active = false;
                                ball.speed.x *= -1;
                            }
                            // Hit right
                            else if (((ball.position.x - ball.radius) <= (brick[i][j].position.x + brickSize.x/2)) &&
                                    ((ball.position.x - ball.radius) > (brick[i][j].position.x + brickSize.x/2 + ball.speed.x)) &&
                                    ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y/2 + ball.radius*2/3)) && (ball.speed.x < 0))
                            {
                                brick[i][j].active = false;
                                ball.speed.x *= -1;
                            }
                        }
                    }
                }

                // Game over logic
                if (player.life <= 0) gameOver = true;
                else
                {
                    gameOver = true;

                    for (int i = 0; i < LINES_OF_BRICKS; i++)
                    {
                        for (int j = 0; j < BRICKS_PER_LINE; j++)
                        {
                            if (brick[i][j].active) gameOver = false;
                        }
                    }
                }
            }
        }
        else
        {
            // if (IsKeyPressed(KEY_ENTER))
            if (HAL::GetButton(GAMEPAD::BTN_START))
            {
                InitGame();
                gameOver = false;
            }
        }
    }

    // Draw game (one frame)
    void DrawGame(void)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!gameOver)
            {
                // Draw player bar
                DrawRectangle(player.position.x - player.size.x/2, player.position.y - player.size.y/2, player.size.x, player.size.y, BLACK);

                // Draw player lives
                for (int i = 0; i < player.life; i++) DrawRectangle(10 + 20*i, screenHeight - 10, 10, 5, LIGHTGRAY);

                // Draw ball
                DrawCircleV(ball.position, ball.radius, MAROON);

                // Draw bricks
                for (int i = 0; i < LINES_OF_BRICKS; i++)
                {
                    for (int j = 0; j < BRICKS_PER_LINE; j++)
                    {
                        if (brick[i][j].active)
                        {
                            if ((i + j) % 2 == 0) DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GRAY);
                            else DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, DARKGRAY);
                        }
                    }
                }

                // if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
                if (pause)
                {
                    HAL::GetCanvas()->setTextColor((uint32_t)GRAY);
                    HAL::GetCanvas()->drawCenterString("GAME PAUSED", 120, 76);
                }
                    

            }
            // else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
            else
            {
                HAL::GetCanvas()->setTextColor((uint32_t)GRAY);
                HAL::GetCanvas()->drawCenterString("PRESS [START]", 120, 76);
                HAL::GetCanvas()->drawCenterString("TO PLAY AGAIN", 120, 100);
            }

        EndDrawing();
    }

    // Unload game variables
    void UnloadGame(void)
    {
        // TODO: Unload all dynamic loaded data (textures, sounds, models...)
    }

    // Update and Draw (one frame)
    void UpdateDrawFrame(void)
    {
        UpdateGame();
        DrawGame();
    }


    void CollisionCallback(void)
    {
        HAL::Beep(GetRandomValue(3000, 6000), 20);
    }
}
