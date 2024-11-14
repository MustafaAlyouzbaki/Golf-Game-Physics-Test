// main.cpp
#include "raylib.h"
#include "Game.h"

int main() {
    // Window dimensions
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    // Initialize game
    InitWindow(screenWidth, screenHeight, "2D Golf Game - Raylib");
    Game game;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update game
        game.Update();
        
        // Dragging controls
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !game.isDragging) {
            if (CheckCollisionPointCircle(GetMousePosition(), game.ballPosition, BALL_RADIUS)) {
                game.isDragging = true;
                game.startDrag = game.ballPosition;
                game.currentDrag = GetMousePosition();
                game.velocity = { 0, 0 };
            }
        } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && game.isDragging) {
            game.currentDrag = GetMousePosition();
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && game.isDragging) {
            Vector2 dragVector = { game.startDrag.x - game.currentDrag.x, game.startDrag.y - game.currentDrag.y };
            game.velocity = { dragVector.x * LAUNCH_SCALE, dragVector.y * LAUNCH_SCALE };
            game.isDragging = false;
            game.isRolling = false;
            game.shotCount += 1;
        }

        // Draw game
        BeginDrawing();
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
