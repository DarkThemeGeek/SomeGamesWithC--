#include "main.hpp"
#include "../../include/raylib/raylib.h"
#include "../../include/raylib/raymath.h"
#include "Core/GameEngine.hpp"
#include "Prefabs/block.hpp"
#include <cstdlib>
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <iostream>

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    FirstGame game{screenWidth, screenHeight, "Lowcost Pong"};
}
void FirstGame::Update() {

    rect.x = GetMouseX();
    Vector2 mouseSpeed = GetMouseDelta() / GetFrameTime();
    float restitution = 0.8f;

    // ball is in window
    // X axis
    if (circle.centre.y > windowHeight * 5 / 6.0f) {
        //  GameOver = true;
    }
    HandleCollisons();
    circle.centre += circle.velocity * GetFrameTime();
}
void FirstGame::Draw() {

    DrawRectangleRec(rect, WHITE);
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 10; j++)
            if (blocks[i][j].alive == true)
                DrawRectangleRec(blocks[i][j].rect, WHITE);
    DrawCircleV({circle.centre.x, circle.centre.y}, circle.radius, BLUE);
    ClearBackground(BLACK);
    DrawFPS(10, 10);

    if (GameOver) {
        DrawText("You Lost", windowWidth / 3, windowHeight * 1 / 2, 48, PURPLE);
    }
}
void FirstGame::Init() {

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 10; j++) {
            blocks[i][j].alive = true;
            blocks[i][j].rect = {i * 60.0f, j * 40.0f, 50, 30};
        }
    SetTargetFPS(120);

    // version  of .super();
    // GameEngine::Game::Init();
}

glm::vec2 FirstGame::GetNormal(Circle &circle, const Rectangle &rect) {
    // Closest point on AABB
    glm::vec2 closest = {
        Clamp(circle.centre.x, rect.x, rect.x + rect.width),
        Clamp(circle.centre.y, rect.y, rect.y + rect.height)};

    glm::vec2 diff = circle.centre - closest;
    float dist2 = glm::dot(diff, diff);

    // Handle "center inside rectangle" case
    if (dist2 < 1e-6f) {
        glm::vec2 rectCenter = {rect.x + rect.width * 0.5f,
                                rect.y + rect.height * 0.5f};

        glm::vec2 d = circle.centre - rectCenter;

        float dx = rect.width * 0.5f - std::abs(d.x);
        float dy = rect.height * 0.5f - std::abs(d.y);

        if (dx < dy) {
            float sign = (d.x > 0) ? 1.0f : -1.0f;
            circle.centre.x += sign * dx;
            return {sign, 0.0f};
        } else {
            float sign = (d.y > 0) ? 1.0f : -1.0f;
            circle.centre.y += sign * dy;
            return {0.0f, sign};
        }
    }

    float dist = std::sqrt(dist2);
    glm::vec2 normal = diff / dist;

    float penetration = circle.radius - dist;

    // Resolve only if moving into surface
    if (penetration > 0.0f) {
        circle.centre += normal * penetration;
    }

    // Snap to axis for stable response
    if (std::abs(diff.x) > std::abs(diff.y)) {
        return {(diff.x > 0) ? 1.0f : -1.0f, 0.0f};
    } else {
        return {0.0f, (diff.y > 0) ? 1.0f : -1.0f};
    }
}
bool FirstGame::IsRunning() {
    return FirstGame::Game::IsRunning() && !GameOver;
}
void FirstGame::Shutdown() {
    if (GameOver)
        WaitTime(5);
    FirstGame::Game::Shutdown();
}
void FirstGame::HandleCollisons() {
    // Handle Collisons Window
    if (circle.centre.x - circle.radius < 0.0f ||
        circle.centre.x + circle.radius > windowWidth) {
        circle.velocity.x *= -1.0f;
    }

    // Y axis
    if (circle.centre.y - circle.radius < 0.0f ||
        circle.centre.y + circle.radius > windowHeight) {
        circle.velocity.y *= -1.0f;
    }
    // checks pallet ball collison
    if (CheckCollisionCircleRec({circle.centre.x, circle.centre.y},
                                circle.radius, rect)) {
        circle.velocity =
            glm::reflect(circle.velocity, GetNormal(circle, rect));
    }
   
    // CheckBlockCollison
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 10; j++) {
            if (blocks[i][j].alive == true)
                if (CheckCollisionCircleRec({circle.centre.x, circle.centre.y},
                                            circle.radius, blocks[i][j].rect)) {
                    blocks[i][j].alive = false;
                    circle.velocity = glm::reflect(
                        circle.velocity, GetNormal(circle, blocks[i][j].rect));
                }

            // std::cout<<std::format("circle centre x:{}
            // y:{}",circle.centre.x,circle.centre.y);
        }
}