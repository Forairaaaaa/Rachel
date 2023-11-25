/**
 * @file snake.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../../hal/hal.h"
#include "../raylib/raylib.h"
#include <cstdint>


namespace SNAKE
{
    /*******************************************************************************************
    *
    *   raylib - classic game: snake
    *
    *   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
    *
    *   This game has been created using raylib v1.3 (www.raylib.com)
    *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
    *
    *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
    *
    ********************************************************************************************/

    // #include "raylib.h"

    #if defined(PLATFORM_WEB)
        #include <emscripten/emscripten.h>
    #endif

    //----------------------------------------------------------------------------------
    // Some Defines
    //----------------------------------------------------------------------------------
    #define SNAKE_LENGTH   256
    // #define SQUARE_SIZE     31
    #define SQUARE_SIZE     12

    //----------------------------------------------------------------------------------
    // Types and Structures Definition
    //----------------------------------------------------------------------------------
    typedef struct Snake {
        Vector2 position;
        Vector2 size;
        Vector2 speed;
        std::uint32_t color;
    } Snake;

    typedef struct Food {
        Vector2 position;
        Vector2 size;
        bool active;
        std::uint32_t color;
    } Food;

    //------------------------------------------------------------------------------------
    // Global Variables Declaration
    //------------------------------------------------------------------------------------
    // static const int screenWidth = 800;
    // static const int screenHeight = 450;
    static const int screenWidth = 240;
    static const int screenHeight = 240;

    // static int framesCounter = 0;
    // static bool gameOver = false;
    // static bool pause = false;

    // static Food fruit = { 0 };
    // static Snake snake[SNAKE_LENGTH] = { 0 };
    // static Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
    // static bool allowMove = false;
    // static Vector2 offset = { 0 };
    // static int counterTail = 0;

    struct Data_t
    {
        int framesCounter = 0;
        bool gameOver = false;
        bool pause = false;

        Food fruit = { 0 };
        Snake snake[SNAKE_LENGTH] = { 0 };
        Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
        bool allowMove = false;
        Vector2 offset = { 0 };
        int counterTail = 0;
    };
    static Data_t* _data = nullptr;



    //------------------------------------------------------------------------------------
    // Module Functions Declaration (local)
    //------------------------------------------------------------------------------------
    static void InitGame(void);         // Initialize game
    static void UpdateGame(void);       // Update game (one frame)
    static void DrawGame(void);         // Draw game (one frame)
    static void UnloadGame(void);       // Unload game
    static void UpdateDrawFrame(void);  // Update and Draw (one frame)

    //------------------------------------------------------------------------------------
    // Program main entry point
    //------------------------------------------------------------------------------------
    int main(void)
    {
        _data = new Data_t;

        // Initialization (Note windowTitle is unused on Android)
        //---------------------------------------------------------
        InitWindow(screenWidth, screenHeight, "classic game: snake");

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

        delete _data;

        return 0;
    }

    //------------------------------------------------------------------------------------
    // Module Functions Definitions (local)
    //------------------------------------------------------------------------------------

    // Initialize game variables
    void InitGame(void)
    {
        _data->framesCounter = 0;
        _data->gameOver = false;
        _data->pause = false;

        _data->counterTail = 1;
        _data->allowMove = false;

        _data->offset.x = screenWidth%SQUARE_SIZE;
        _data->offset.y = screenHeight%SQUARE_SIZE;

        for (int i = 0; i < SNAKE_LENGTH; i++)
        {
            _data->snake[i].position = (Vector2){ _data->offset.x/2, _data->offset.y/2 };
            _data->snake[i].size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
            _data->snake[i].speed = (Vector2){ SQUARE_SIZE, 0 };

            if (i == 0) _data->snake[i].color = DARKBLUE;
            else _data->snake[i].color = BLUE;
        }

        for (int i = 0; i < SNAKE_LENGTH; i++)
        {
            _data->snakePosition[i] = (Vector2){ 0.0f, 0.0f };
        }

        _data->fruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
        _data->fruit.color = SKYBLUE;
        _data->fruit.active = false;
    }

    // Update game (one frame)
    void UpdateGame(void)
    {
        if (!_data->gameOver)
        {
            // if (IsKeyPressed('P')) pause = !pause;
            if (HAL::GetButton(GAMEPAD::BTN_START))
            {
                while (HAL::GetButton(GAMEPAD::BTN_START))
                    HAL::Delay(50);

                _data->pause = !_data->pause;
            }

            if (!_data->pause)
            {
                // Player control
                // if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove)
                if (HAL::GetButton(GAMEPAD::BTN_RIGHT) && (_data->snake[0].speed.x == 0) && _data->allowMove)
                {
                    _data->snake[0].speed = (Vector2){ SQUARE_SIZE, 0 };
                    _data->allowMove = false;
                }
                // if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove)
                if (HAL::GetButton(GAMEPAD::BTN_LEFT) && (_data->snake[0].speed.x == 0) && _data->allowMove)
                {
                    _data->snake[0].speed = (Vector2){ -SQUARE_SIZE, 0 };
                    _data->allowMove = false;
                }
                // if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove)
                if (HAL::GetButton(GAMEPAD::BTN_UP) && (_data->snake[0].speed.y == 0) && _data->allowMove)
                {
                    _data->snake[0].speed = (Vector2){ 0, -SQUARE_SIZE };
                    _data->allowMove = false;
                }
                // if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove)
                if (HAL::GetButton(GAMEPAD::BTN_DOWN) && (_data->snake[0].speed.y == 0) && _data->allowMove)
                {
                    _data->snake[0].speed = (Vector2){ 0, SQUARE_SIZE };
                    _data->allowMove = false;
                }

                // Snake movement
                for (int i = 0; i < _data->counterTail; i++) _data->snakePosition[i] = _data->snake[i].position;

                if ((_data->framesCounter%5) == 0)
                {
                    for (int i = 0; i < _data->counterTail; i++)
                    {
                        if (i == 0)
                        {
                            _data->snake[0].position.x += _data->snake[0].speed.x;
                            _data->snake[0].position.y += _data->snake[0].speed.y;
                            _data->allowMove = true;
                        }
                        else _data->snake[i].position = _data->snakePosition[i-1];
                    }
                }

                // Wall behaviour
                if (((_data->snake[0].position.x) > (screenWidth - _data->offset.x)) ||
                    ((_data->snake[0].position.y) > (screenHeight - _data->offset.y)) ||
                    (_data->snake[0].position.x < 0) || (_data->snake[0].position.y < 0))
                {
                    _data->gameOver = true;
                }

                // Collision with yourself
                for (int i = 1; i < _data->counterTail; i++)
                {
                    if ((_data->snake[0].position.x == _data->snake[i].position.x) && (_data->snake[0].position.y == _data->snake[i].position.y)) _data->gameOver = true;
                }

                // Fruit position calculation
                if (!_data->fruit.active)
                {
                    _data->fruit.active = true;
                    _data->fruit.position = (Vector2){ GetRandomValue(0, (screenWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + _data->offset.x/2, GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + _data->offset.y/2 };

                    for (int i = 0; i < _data->counterTail; i++)
                    {
                        while ((_data->fruit.position.x == _data->snake[i].position.x) && (_data->fruit.position.y == _data->snake[i].position.y))
                        {
                            _data->fruit.position = (Vector2){ GetRandomValue(0, (screenWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + _data->offset.x/2, GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + _data->offset.y/2 };
                            i = 0;
                        }
                    }
                }

                // Collision
                if ((_data->snake[0].position.x < (_data->fruit.position.x + _data->fruit.size.x) && (_data->snake[0].position.x + _data->snake[0].size.x) > _data->fruit.position.x) &&
                    (_data->snake[0].position.y < (_data->fruit.position.y + _data->fruit.size.y) && (_data->snake[0].position.y + _data->snake[0].size.y) > _data->fruit.position.y))
                {
                    _data->snake[_data->counterTail].position = _data->snakePosition[_data->counterTail - 1];
                    _data->counterTail += 1;
                    _data->fruit.active = false;
                }

                _data->framesCounter++;
            }
        }
        else
        {
            // if (IsKeyPressed(KEY_ENTER))
            if (HAL::GetButton(GAMEPAD::BTN_START))
            {
                while (HAL::GetButton(GAMEPAD::BTN_START))
                    HAL::Delay(50);
                
                InitGame();
                _data->gameOver = false;
            }
        }
    }

    // Draw game (one frame)
    void DrawGame(void)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!_data->gameOver)
            {
                // Draw grid lines
                for (int i = 0; i < screenWidth/SQUARE_SIZE + 1; i++)
                {
                    DrawLineV((Vector2){SQUARE_SIZE*i + _data->offset.x/2, _data->offset.y/2}, (Vector2){SQUARE_SIZE*i + _data->offset.x/2, screenHeight - _data->offset.y/2}, LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight/SQUARE_SIZE + 1; i++)
                {
                    DrawLineV((Vector2){_data->offset.x/2, SQUARE_SIZE*i + _data->offset.y/2}, (Vector2){screenWidth - _data->offset.x/2, SQUARE_SIZE*i + _data->offset.y/2}, LIGHTGRAY);
                }

                // Draw snake
                for (int i = 0; i < _data->counterTail; i++) DrawRectangleV(_data->snake[i].position, _data->snake[i].size, _data->snake[i].color);

                // Draw fruit to pick
                DrawRectangleV(_data->fruit.position, _data->fruit.size, _data->fruit.color);

                // if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
                if (_data->pause)
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
}
