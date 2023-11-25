/**
 * @file tetris.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../../hal/hal.h"
#include "../raylib/raylib.h"
#include <cstdint>


namespace TETRIS
{
    /*******************************************************************************************
    *
    *   raylib - classic game: tetris
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
    // #define SQUARE_SIZE             20
    // #define SQUARE_SIZE             10
    #define SQUARE_SIZE             12

    #define GRID_HORIZONTAL_SIZE    12
    #define GRID_VERTICAL_SIZE      20

    // #define LATERAL_SPEED           10
    #define LATERAL_SPEED           5
    #define TURNING_SPEED           12
    #define FAST_FALL_AWAIT_COUNTER 30

    #define FADING_TIME             33

    //----------------------------------------------------------------------------------
    // Types and Structures Definition
    //----------------------------------------------------------------------------------
    typedef enum GridSquare { EMPTY, MOVING, FULL, BLOCK, FADING } GridSquare;

    //------------------------------------------------------------------------------------
    // Global Variables Declaration
    //------------------------------------------------------------------------------------
    // static const int screenWidth = 800;
    // static const int screenHeight = 450;
    static const int screenWidth = 240;
    static const int screenHeight = 240;

    // static bool gameOver = false;
    // static bool pause = false;

    // // Matrices
    // static GridSquare grid [GRID_HORIZONTAL_SIZE][GRID_VERTICAL_SIZE];
    // static GridSquare piece [4][4];
    // static GridSquare incomingPiece [4][4];

    // // Theese variables keep track of the active piece position
    // static int piecePositionX = 0;
    // static int piecePositionY = 0;

    // // Game parameters
    // static std::uint32_t fadingColor;
    // //static int fallingSpeed;           // In frames

    // static bool beginPlay = true;      // This var is only true at the begining of the game, used for the first matrix creations
    // static bool pieceActive = false;
    // static bool detection = false;
    // static bool lineToDelete = false;

    // // Statistics
    // static int level = 1;
    // static int lines = 0;

    // // Counters
    // static int gravityMovementCounter = 0;
    // static int lateralMovementCounter = 0;
    // static int turnMovementCounter = 0;
    // static int fastFallMovementCounter = 0;

    // static int fadeLineCounter = 0;

    // // Based on level
    // static int gravitySpeed = 30;


    struct Data_t
    {
        bool gameOver = false;
        bool pause = false;
        GridSquare grid [GRID_HORIZONTAL_SIZE][GRID_VERTICAL_SIZE];
        GridSquare piece [4][4];
        GridSquare incomingPiece [4][4];
        int piecePositionX = 0;
        int piecePositionY = 0;
        std::uint32_t fadingColor;
        bool beginPlay = true;
        bool pieceActive = false;
        bool detection = false;
        bool lineToDelete = false;
        int level = 1;
        int lines = 0;
        int gravityMovementCounter = 0;
        int lateralMovementCounter = 0;
        int turnMovementCounter = 0;
        int fastFallMovementCounter = 0;
        int fadeLineCounter = 0;
        int gravitySpeed = 30;
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

    // Additional module functions
    static bool Createpiece();
    static void GetRandompiece();
    static void ResolveFallingMovement(bool *detection, bool *pieceActive);
    static bool ResolveLateralMovement();
    static bool ResolveTurnMovement();
    static void CheckDetection(bool *detection);
    static void CheckCompletion(bool *lineToDelete);
    static int DeleteCompleteLines();

    //------------------------------------------------------------------------------------
    // Program main entry point
    //------------------------------------------------------------------------------------
    int main(void)
    {
        _data = new Data_t;

        // Initialization (Note windowTitle is unused on Android)
        //---------------------------------------------------------
        InitWindow(screenWidth, screenHeight, "classic game: tetris");

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

    //--------------------------------------------------------------------------------------
    // Game Module Functions Definition
    //--------------------------------------------------------------------------------------

    // Initialize game variables
    void InitGame(void)
    {
        // Initialize game statistics
        _data->level = 1;
        _data->lines = 0;

        _data->fadingColor = GRAY;

        _data->piecePositionX = 0;
        _data->piecePositionY = 0;

        _data->pause = false;

        _data->beginPlay = true;
        _data->pieceActive = false;
        _data->detection = false;
        _data->lineToDelete = false;

        // Counters
        _data->gravityMovementCounter = 0;
        _data->lateralMovementCounter = 0;
        _data->turnMovementCounter = 0;
        _data->fastFallMovementCounter = 0;

        _data->fadeLineCounter = 0;
        _data->gravitySpeed = 30;

        // Initialize grid matrices
        for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
        {
            for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
            {
                if ((j == GRID_VERTICAL_SIZE - 1) || (i == 0) || (i == GRID_HORIZONTAL_SIZE - 1)) _data->grid[i][j] = BLOCK;
                else _data->grid[i][j] = EMPTY;
            }
        }

        // Initialize incoming piece matrices
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j< 4; j++)
            {
                _data->incomingPiece[i][j] = EMPTY;
            }
        }
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
                if (!_data->lineToDelete)
                {
                    if (!_data->pieceActive)
                    {
                        // Get another piece
                        _data->pieceActive = Createpiece();

                        // We leave a little time before starting the fast falling down
                        _data->fastFallMovementCounter = 0;
                    }
                    else    // Piece falling
                    {
                        // Counters update
                        _data->fastFallMovementCounter++;
                        _data->gravityMovementCounter++;
                        _data->lateralMovementCounter++;
                        _data->turnMovementCounter++;

                        // We make sure to move if we've pressed the key this frame
                        // if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) lateralMovementCounter = LATERAL_SPEED;
                        // if (HAL::GetButton(GAMEPAD::BTN_LEFT) || HAL::GetButton(GAMEPAD::BTN_RIGHT)) 
                        //     lateralMovementCounter = LATERAL_SPEED;

                        // if (IsKeyPressed(KEY_UP)) turnMovementCounter = TURNING_SPEED;
                        if (HAL::GetButton(GAMEPAD::BTN_UP)) 
                            _data->turnMovementCounter = TURNING_SPEED;

                        // Fall down
                        // if (IsKeyDown(KEY_DOWN) && (fastFallMovementCounter >= FAST_FALL_AWAIT_COUNTER))
                        if (HAL::GetButton(GAMEPAD::BTN_DOWN) && (_data->fastFallMovementCounter >= FAST_FALL_AWAIT_COUNTER))
                        {
                            // We make sure the piece is going to fall this frame
                            _data->gravityMovementCounter += _data->gravitySpeed;
                        }

                        if (_data->gravityMovementCounter >= _data->gravitySpeed)
                        {
                            // Basic falling movement
                            CheckDetection(&_data->detection);

                            // Check if the piece has collided with another piece or with the boundings
                            ResolveFallingMovement(&_data->detection, &_data->pieceActive);

                            // Check if we fullfilled a line and if so, erase the line and pull down the the lines above
                            CheckCompletion(&_data->lineToDelete);

                            _data->gravityMovementCounter = 0;
                        }

                        // Move laterally at player's will
                        if (_data->lateralMovementCounter >= LATERAL_SPEED)
                        {
                            // Update the lateral movement and if success, reset the lateral counter
                            if (!ResolveLateralMovement()) _data->lateralMovementCounter = 0;
                        }

                        // Turn the piece at player's will
                        if (_data->turnMovementCounter >= TURNING_SPEED)
                        {
                            // Update the turning movement and reset the turning counter
                            if (ResolveTurnMovement()) _data->turnMovementCounter = 0;
                        }
                    }

                    // Game over logic
                    for (int j = 0; j < 2; j++)
                    {
                        for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                        {
                            if (_data->grid[i][j] == FULL)
                            {
                                _data->gameOver = true;
                            }
                        }
                    }
                }
                else
                {
                    // Animation when deleting lines
                    _data->fadeLineCounter++;

                    if (_data->fadeLineCounter%8 < 4) _data->fadingColor = MAROON;
                    else _data->fadingColor = GRAY;

                    if (_data->fadeLineCounter >= FADING_TIME)
                    {
                        int deletedLines = 0;
                        deletedLines = DeleteCompleteLines();
                        _data->fadeLineCounter = 0;
                        _data->lineToDelete = false;

                        _data->lines += deletedLines;
                    }
                }
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
                // Draw gameplay area
                Vector2 offset;
                // offset.x = screenWidth/2 - (GRID_HORIZONTAL_SIZE*SQUARE_SIZE/2) - 50;
                // offset.y = screenHeight/2 - ((GRID_VERTICAL_SIZE - 1)*SQUARE_SIZE/2) + SQUARE_SIZE*2;

                // offset.y -= 50;     // NOTE: Harcoded position!
                offset.x = SQUARE_SIZE;

                int controller = offset.x;

                for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
                {
                    for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
                    {
                        // Draw each square of the grid
                        if (_data->grid[i][j] == EMPTY)
                        {
                            DrawLine(offset.x, offset.y, offset.x + SQUARE_SIZE, offset.y, LIGHTGRAY );
                            DrawLine(offset.x, offset.y, offset.x, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(offset.x + SQUARE_SIZE, offset.y, offset.x + SQUARE_SIZE, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(offset.x, offset.y + SQUARE_SIZE, offset.x + SQUARE_SIZE, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            offset.x += SQUARE_SIZE;
                        }
                        else if (_data->grid[i][j] == FULL)
                        {
                            DrawRectangle(offset.x, offset.y, SQUARE_SIZE, SQUARE_SIZE, GRAY);
                            offset.x += SQUARE_SIZE;
                        }
                        else if (_data->grid[i][j] == MOVING)
                        {
                            DrawRectangle(offset.x, offset.y, SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
                            offset.x += SQUARE_SIZE;
                        }
                        else if (_data->grid[i][j] == BLOCK)
                        {
                            DrawRectangle(offset.x, offset.y, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);
                            offset.x += SQUARE_SIZE;
                        }
                        else if (_data->grid[i][j] == FADING)
                        {
                            DrawRectangle(offset.x, offset.y, SQUARE_SIZE, SQUARE_SIZE, _data->fadingColor);
                            offset.x += SQUARE_SIZE;
                        }
                    }

                    offset.x = controller;
                    offset.y += SQUARE_SIZE;
                }

                // Draw incoming piece (hardcoded)
                // offset.x = 500;
                // offset.y = 45;
                offset.x = 174;
                offset.y = 32;

                int controler = offset.x;

                for (int j = 0; j < 4; j++)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (_data->incomingPiece[i][j] == EMPTY)
                        {
                            DrawLine(offset.x, offset.y, offset.x + SQUARE_SIZE, offset.y, LIGHTGRAY );
                            DrawLine(offset.x, offset.y, offset.x, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(offset.x + SQUARE_SIZE, offset.y, offset.x + SQUARE_SIZE, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(offset.x, offset.y + SQUARE_SIZE, offset.x + SQUARE_SIZE, offset.y + SQUARE_SIZE, LIGHTGRAY );
                            offset.x += SQUARE_SIZE;
                        }
                        else if (_data->incomingPiece[i][j] == MOVING)
                        {
                            DrawRectangle(offset.x, offset.y, SQUARE_SIZE, SQUARE_SIZE, GRAY);
                            offset.x += SQUARE_SIZE;
                        }
                    }

                    offset.x = controler;
                    offset.y += SQUARE_SIZE;
                }

                // DrawText("INCOMING:", offset.x, offset.y - 100, 10, GRAY);
                // DrawText(TextFormat("LINES:      %04i", lines), offset.x, offset.y + 20, 10, GRAY);

                HAL::GetCanvas()->setTextColor((uint32_t)GRAY);
                HAL::GetCanvas()->setCursor(168, 150);
                HAL::GetCanvas()->printf("LINES");
                HAL::GetCanvas()->setCursor(174, 180);
                HAL::GetCanvas()->printf("%04d", _data->lines);


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

    //--------------------------------------------------------------------------------------
    // Additional module functions
    //--------------------------------------------------------------------------------------
    static bool Createpiece()
    {
        _data->piecePositionX = (int)((GRID_HORIZONTAL_SIZE - 4)/2);
        _data->piecePositionY = 0;

        // If the game is starting and you are going to create the first piece, we create an extra one
        if (_data->beginPlay)
        {
            GetRandompiece();
            _data->beginPlay = false;
        }

        // We assign the incoming piece to the actual piece
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j< 4; j++)
            {
                _data->piece[i][j] = _data->incomingPiece[i][j];
            }
        }

        // We assign a random piece to the incoming one
        GetRandompiece();

        // Assign the piece to the grid
        for (int i = _data->piecePositionX; i < _data->piecePositionX + 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (_data->piece[i - (int)_data->piecePositionX][j] == MOVING) _data->grid[i][j] = MOVING;
            }
        }

        return true;
    }

    static void GetRandompiece()
    {
        int random = GetRandomValue(0, 6);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                _data->incomingPiece[i][j] = EMPTY;
            }
        }

        switch (random)
        {
            case 0: { _data->incomingPiece[1][1] = MOVING; _data->incomingPiece[2][1] = MOVING; _data->incomingPiece[1][2] = MOVING; _data->incomingPiece[2][2] = MOVING; } break;    //Cube
            case 1: { _data->incomingPiece[1][0] = MOVING; _data->incomingPiece[1][1] = MOVING; _data->incomingPiece[1][2] = MOVING; _data->incomingPiece[2][2] = MOVING; } break;    //L
            case 2: { _data->incomingPiece[1][2] = MOVING; _data->incomingPiece[2][0] = MOVING; _data->incomingPiece[2][1] = MOVING; _data->incomingPiece[2][2] = MOVING; } break;    //L inversa
            case 3: { _data->incomingPiece[0][1] = MOVING; _data->incomingPiece[1][1] = MOVING; _data->incomingPiece[2][1] = MOVING; _data->incomingPiece[3][1] = MOVING; } break;    //Recta
            case 4: { _data->incomingPiece[1][0] = MOVING; _data->incomingPiece[1][1] = MOVING; _data->incomingPiece[1][2] = MOVING; _data->incomingPiece[2][1] = MOVING; } break;    //Creu tallada
            case 5: { _data->incomingPiece[1][1] = MOVING; _data->incomingPiece[2][1] = MOVING; _data->incomingPiece[2][2] = MOVING; _data->incomingPiece[3][2] = MOVING; } break;    //S
            case 6: { _data->incomingPiece[1][2] = MOVING; _data->incomingPiece[2][2] = MOVING; _data->incomingPiece[2][1] = MOVING; _data->incomingPiece[3][1] = MOVING; } break;    //S inversa
        }
    }

    static void ResolveFallingMovement(bool *detection, bool *pieceActive)
    {
        // If we finished moving this piece, we stop it
        if (*detection)
        {
            for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    if (_data->grid[i][j] == MOVING)
                    {
                        _data->grid[i][j] = FULL;
                        *detection = false;
                        *pieceActive = false;
                    }
                }
            }
        }
        else    // We move down the piece
        {
            for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    if (_data->grid[i][j] == MOVING)
                    {
                        _data->grid[i][j+1] = MOVING;
                        _data->grid[i][j] = EMPTY;
                    }
                }
            }

            _data->piecePositionY++;
        }
    }

    static bool ResolveLateralMovement()
    {
        bool collision = false;

        // Piece movement
        // if (IsKeyDown(KEY_LEFT))        // Move left
        if (HAL::GetButton(GAMEPAD::BTN_LEFT))
        {
            // Check if is possible to move to left
            for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    if (_data->grid[i][j] == MOVING)
                    {
                        // Check if we are touching the left wall or we have a full square at the left
                        if ((i-1 == 0) || (_data->grid[i-1][j] == FULL)) collision = true;
                    }
                }
            }

            // If able, move left
            if (!collision)
            {
                for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
                {
                    for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)             // We check the matrix from left to right
                    {
                        // Move everything to the left
                        if (_data->grid[i][j] == MOVING)
                        {
                            _data->grid[i-1][j] = MOVING;
                            _data->grid[i][j] = EMPTY;
                        }
                    }
                }

                _data->piecePositionX--;
            }
        }
        // else if (IsKeyDown(KEY_RIGHT))  // Move right
        if (HAL::GetButton(GAMEPAD::BTN_RIGHT))
        {
            // Check if is possible to move to right
            for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    if (_data->grid[i][j] == MOVING)
                    {
                        // Check if we are touching the right wall or we have a full square at the right
                        if ((i+1 == GRID_HORIZONTAL_SIZE - 1) || (_data->grid[i+1][j] == FULL))
                        {
                            collision = true;

                        }
                    }
                }
            }

            // If able move right
            if (!collision)
            {
                for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
                {
                    for (int i = GRID_HORIZONTAL_SIZE - 1; i >= 1; i--)             // We check the matrix from right to left
                    {
                        // Move everything to the right
                        if (_data->grid[i][j] == MOVING)
                        {
                            _data->grid[i+1][j] = MOVING;
                            _data->grid[i][j] = EMPTY;
                        }
                    }
                }

                _data->piecePositionX++;
            }
        }

        return collision;
    }

    static bool ResolveTurnMovement()
    {
        // Input for turning the piece
        // if (IsKeyDown(KEY_UP))
        if (HAL::GetButton(GAMEPAD::BTN_UP))
        {
            GridSquare aux;
            bool checker = false;

            // Check all turning possibilities
            if ((_data->grid[_data->piecePositionX + 3][_data->piecePositionY] == MOVING) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY] != EMPTY) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 3] == MOVING) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX][_data->piecePositionY + 3] == MOVING) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 3] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 3] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX][_data->piecePositionY] == MOVING) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 3] != EMPTY) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 3] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 1][_data->piecePositionY] == MOVING) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 2] != EMPTY) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 2] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 1] == MOVING) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 3] == MOVING) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 1] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 1] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX][_data->piecePositionY + 2] == MOVING) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 3] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 3] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 2][_data->piecePositionY] == MOVING) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 1] != EMPTY) &&
                (_data->grid[_data->piecePositionX][_data->piecePositionY + 1] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 2] == MOVING) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 3] == MOVING) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 2] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 3][_data->piecePositionY + 2] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX][_data->piecePositionY + 1] == MOVING) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 3] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 3] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 1] == MOVING) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 2] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 2] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 1] == MOVING) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 1] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 1] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 2] == MOVING) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 1] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 1] != MOVING)) checker = true;

            if ((_data->grid[_data->piecePositionX + 1][_data->piecePositionY + 2] == MOVING) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 2] != EMPTY) &&
                (_data->grid[_data->piecePositionX + 2][_data->piecePositionY + 2] != MOVING)) checker = true;

            if (!checker)
            {
                aux = _data->piece[0][0];
                _data->piece[0][0] = _data->piece[3][0];
                _data->piece[3][0] = _data->piece[3][3];
                _data->piece[3][3] = _data->piece[0][3];
                _data->piece[0][3] = aux;

                aux = _data->piece[1][0];
                _data->piece[1][0] = _data->piece[3][1];
                _data->piece[3][1] = _data->piece[2][3];
                _data->piece[2][3] = _data->piece[0][2];
                _data->piece[0][2] = aux;

                aux = _data->piece[2][0];
                _data->piece[2][0] = _data->piece[3][2];
                _data->piece[3][2] = _data->piece[1][3];
                _data->piece[1][3] = _data->piece[0][1];
                _data->piece[0][1] = aux;

                aux = _data->piece[1][1];
                _data->piece[1][1] = _data->piece[2][1];
                _data->piece[2][1] = _data->piece[2][2];
                _data->piece[2][2] = _data->piece[1][2];
                _data->piece[1][2] = aux;
            }

            for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    if (_data->grid[i][j] == MOVING)
                    {
                        _data->grid[i][j] = EMPTY;
                    }
                }
            }

            for (int i = _data->piecePositionX; i < _data->piecePositionX + 4; i++)
            {
                for (int j = _data->piecePositionY; j < _data->piecePositionY + 4; j++)
                {
                    if (_data->piece[i - _data->piecePositionX][j - _data->piecePositionY] == MOVING)
                    {
                        _data->grid[i][j] = MOVING;
                    }
                }
            }

            return true;
        }

        return false;
    }

    static void CheckDetection(bool *detection)
    {
        for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
        {
            for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
            {
                if ((_data->grid[i][j] == MOVING) && ((_data->grid[i][j+1] == FULL) || (_data->grid[i][j+1] == BLOCK))) *detection = true;
            }
        }
    }

    static void CheckCompletion(bool *lineToDelete)
    {
        int calculator = 0;

        for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
        {
            calculator = 0;
            for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
            {
                // Count each square of the line
                if (_data->grid[i][j] == FULL)
                {
                    calculator++;
                }

                // Check if we completed the whole line
                if (calculator == GRID_HORIZONTAL_SIZE - 2)
                {
                    *lineToDelete = true;
                    calculator = 0;
                    // points++;

                    // Mark the completed line
                    for (int z = 1; z < GRID_HORIZONTAL_SIZE - 1; z++)
                    {
                        _data->grid[z][j] = FADING;
                    }
                }
            }
        }
    }

    static int DeleteCompleteLines()
    {
        int deletedLines = 0;

        // Erase the completed line
        for (int j = GRID_VERTICAL_SIZE - 2; j >= 0; j--)
        {
            while (_data->grid[1][j] == FADING)
            {
                for (int i = 1; i < GRID_HORIZONTAL_SIZE - 1; i++)
                {
                    _data->grid[i][j] = EMPTY;
                }

                for (int j2 = j-1; j2 >= 0; j2--)
                {
                    for (int i2 = 1; i2 < GRID_HORIZONTAL_SIZE - 1; i2++)
                    {
                        if (_data->grid[i2][j2] == FULL)
                        {
                            _data->grid[i2][j2+1] = FULL;
                            _data->grid[i2][j2] = EMPTY;
                        }
                        else if (_data->grid[i2][j2] == FADING)
                        {
                            _data->grid[i2][j2+1] = FADING;
                            _data->grid[i2][j2] = EMPTY;
                        }
                    }
                }

                deletedLines++;
            }
        }

        return deletedLines;
    }
}
