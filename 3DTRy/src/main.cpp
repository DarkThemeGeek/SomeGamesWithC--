#include "main.hpp"
#include "../../include/raylib/raylib.h"
#include "../../include/raylib/raymath.h"
#include "Core/GameEngine.hpp"
#include <cstdlib>
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <iostream>

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    FirstGame game{screenWidth, screenHeight, "3D Something"};
    game.run();
}

bool FirstGame::IsRunning() { return GameEngine::Game::IsRunning(); };
void FirstGame::Update() { 
    UpdateCamera(&camera, CAMERA_FREE);
    
 };
void FirstGame::Draw() {

    DrawGrid(100, 1.0f);
    DrawCube({0, 1, 0}, 1, 1, 1, RED);

   
};
void FirstGame::Init() {};
void FirstGame::Shutdown() { GameEngine::Game::Shutdown(); };

void FirstGame::SetupCamera(Camera3D &camera) {
    camera.position = {5.0f, 5.0f, 5.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
};