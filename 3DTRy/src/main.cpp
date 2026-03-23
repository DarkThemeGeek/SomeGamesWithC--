#include "main.hpp"
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include "Core/GameEngine.hpp"
#include <cstdlib>
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
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
    // if (IsWindowFocused()){

    //     HideCursor();
    //     DisableCursor();
    //     SetMousePosition(windowWidth / 2, windowHeight / 2);
    // }
    player.Walk();
    UpdateCamera(&camera, CAMERA_FREE);
};
void FirstGame::Draw() {

    DrawGrid(100, 1.0f);
    player.Draw();
    DrawCube({3, 0, 0}, 10, 1, 50, RED);
};
void FirstGame::Init() {

    player.speed = glm::vec3{0, 0, 1};
    camera.position = {player.position.x, player.position.y+10, player.position.z-10};
    

};
void FirstGame::Shutdown() { GameEngine::Game::Shutdown(); };

void FirstGame::SetupCamera(Camera3D &camera) {
    camera.position = {5.0f, 5.0f, 5.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
};