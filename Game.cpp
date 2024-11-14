// Game.cpp
#include "Game.h"

// Constructor
Game::Game() {
    ballPosition = { BALL_RADIUS + 100, GetScreenHeight() - BALL_RADIUS };
    velocity = { 0, 0 };
    isRolling = false;
    isDragging = false;
    shotCount = 0;
    scoreCount = 0;
}

// Update the game state
void Game::Update() {
    if (!isDragging) {
        ballPosition.x += velocity.x;
        ballPosition.y += velocity.y;
        
        // Apply gravity
        velocity.y += GRAVITY;
        
        // Check for collisions
        CheckCollisions();
        
        // Apply friction if rolling
        ApplyFriction();
    }
}

// Draw the game elements
void Game::Draw() {
    // Draw background
    ClearBackground(SKYBLUE);
    
    // Draw grass
    DrawRectangle(0, GetScreenHeight() - GRASS_HEIGHT, GetScreenWidth(), GRASS_HEIGHT, GREEN);
    
    // Draw ball
    DrawCircleV(ballPosition, BALL_RADIUS, WHITE);
    DrawCircleLines(ballPosition.x, ballPosition.y, BALL_RADIUS, BLACK);
    
    // Draw stats
    DrawText(TextFormat("Shots: %d", shotCount), 25, 50, 36, BLACK);
    DrawText(TextFormat("Score: %d", scoreCount), 25, 100, 36, BLACK);
    
    // Draw drag line
    if (isDragging) {
        DrawLineV(startDrag, currentDrag, WHITE);
    }
}

// Reset game
void Game::ResetGame() {
    ballPosition = { BALL_RADIUS + 100, GetScreenHeight() - BALL_RADIUS };
    velocity = { 0, 0 };
    isRolling = false;
    shotCount = 0;
}

// Check collisions
void Game::CheckCollisions() {
    // Floor collision
    if (ballPosition.y > GetScreenHeight() - GRASS_HEIGHT - BALL_RADIUS) {
        ballPosition.y = GetScreenHeight() - GRASS_HEIGHT - BALL_RADIUS;
        
        if (fabs(velocity.y) < STOP_THRESHOLD) {
            velocity.y = 0;
            isRolling = true;
        } else {
            isRolling = false;
            velocity.y *= -DAMPING;
        }
    }
    
    // Side wall collisions
    if (ballPosition.x < BALL_RADIUS) {
        ballPosition.x = BALL_RADIUS;
        velocity.x *= -DAMPING;
    } else if (ballPosition.x > GetScreenWidth() - BALL_RADIUS) {
        ballPosition.x = GetScreenWidth() - BALL_RADIUS;
        velocity.x *= -DAMPING;
    }
    
    // Top wall collision
    if (ballPosition.y < BALL_RADIUS) {
        ballPosition.y = BALL_RADIUS;
        velocity.y *= -DAMPING;
    }
}

// Apply friction with surface
void Game::ApplyFriction() {
    if (isRolling) {
        velocity.x *= FRICTION;
        if (fabs(velocity.x) < 0.1f) {
            velocity.x = 0;
        }
    }
}