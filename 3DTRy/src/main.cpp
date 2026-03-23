#include "main.hpp"
#include "Core/GameEngine.hpp"
#include "Prefabs/obstacle.hpp"
#include <cstdlib>
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <raylib/raylib.h>
#include <raylib/raymath.h>

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    FirstGame game{screenWidth, screenHeight, "3D Something"};
    game.run();
}

bool FirstGame::IsRunning() {
    return GameEngine::Game::IsRunning() && !player.dead;
};
void FirstGame::Update(float dt) {

    Movement(dt);
    CheckCollisons();
    for (auto &obstacle : obstacles) {
        obstacle.Move();
    }
    UpdateCamera(&camera, CAMERA_FREE);
};
void FirstGame::Draw() {

    DrawGrid(100, 1.0f);
    player.Draw();
    for (const auto &obstacle : obstacles) {
        obstacle.Draw();
    }
    DrawCube({3, 0, 0}, 10, 1, 50, RED);
};
void FirstGame::Init() {

    player.speed = glm::vec3{0, 0, 1};
    camera.position = {player.position.x, player.position.y + 10,
                       player.position.z - 10};
    obstacles.push_back(
        Obstacle{glm::vec3{1, 1.5, 7}, glm::vec3{2, 2, 1}, BLUE, PlayerSpeed});
    obstacles.push_back(
        Obstacle{glm::vec3{3, 1.5, 5}, glm::vec3{2, 2, 1}, BLUE, PlayerSpeed});
    obstacles.push_back(
        Obstacle{glm::vec3{5, 1.5, 5}, glm::vec3{2, 2, 1}, BLUE, PlayerSpeed});
};
void FirstGame::Shutdown() {
    if (player.dead) {
        BeginDrawing();
        DrawText("You died", windowWidth / 3, windowHeight / 2, 100,
                 DARKPURPLE);

        EndDrawing();
        WaitTime(2);
    }

    GameEngine::Game::Shutdown();
};

void FirstGame::SetupCamera(Camera3D &camera) {
    camera.position = {5.0f, 5.0f, 5.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
};
void FirstGame::CheckCollisons() {
    for (const auto &obstacle : obstacles) {
        if (player.CheckFront(ToBoundingBox(obstacle.position, obstacle.size))) {
            player.dead = true;
            return;
        }
    }
}
Vector3 ToVec3(glm::vec3 &vec) { return {vec.x, vec.y, vec.z}; }
BoundingBox ToBoundingBox(const glm::vec3 &vec, const glm::vec3 &size) {
    return {{vec.x, vec.y, vec.z},
            {vec.x + size.x, vec.y + size.y, vec.z + size.z}};
}
//
float vy = 0;         // Vertical velocity
float gravity = -15;  // Pixels per second² (negative = downward)
float jumpForce = 10; // Initial jump velocity
float groundY = 1.5;  // The y-position of the ground
void FirstGame::Movement(float dt) {
    if (IsKeyPressed(jump) && !player.isJumping) {
        player.isJumping = true;
        vy = jumpForce;
    }
    player.position.y += vy * dt;
    vy += gravity * dt;
    if (player.position.y <= groundY) {
        player.position.y = groundY;
        vy = 0;
        player.isJumping = false;
    }
}