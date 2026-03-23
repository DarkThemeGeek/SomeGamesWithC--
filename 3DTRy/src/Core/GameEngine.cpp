#include "GameEngine.hpp"

void GameEngine::Game::MainLoop(Camera3D& camera) {
    InitWindow(windowWidth, windowHeight, title.c_str());
    Init();
    while (IsRunning()) {
        // calculations before it
        Update();
        // Drawing
        BeginDrawing();
       
        BeginMode3D(camera);
        ClearBackground(RAYWHITE);

        Draw();
        EndMode3D();
        EndDrawing();
       
        
    }
    Shutdown();
} 
   /**const float fixedDt = 1.0f / 60.0f;
float accumulator = 0.0f;

while (!WindowShouldClose()) {
    accumulator += GetFrameTime();

    while (accumulator >= fixedDt) {
        UpdatePhysics(fixedDt);
        accumulator -= fixedDt;
    }
} */


GameEngine::Game::Game(int width, int height, std::string title)
    : windowWidth(width), windowHeight(height), title(title) {}