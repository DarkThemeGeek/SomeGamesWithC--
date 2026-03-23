#pragma once
#include "capsule.hpp"
#include "raylib/raylib.h"
#include <glm/ext/vector_float3.hpp>
class Player : public Capsule {
  public:
    // very complicated state machine dead or not dead
    bool dead = false;
    bool isJumping = false;
    Player(glm::vec3 position, float radius, float height, Color color)
        : Capsule(position, radius, height, color) {}
    void Draw() { Capsule::Draw(); }
    void Walk() { position += speed * GetFrameTime(); }
    glm::vec3 speed;
    bool CheckFront(BoundingBox box) {
        // Player box
        BoundingBox playerBox;
        playerBox.min = {position.x - radius / 2, position.y,
                         position.z - radius / 2};
        playerBox.max = {position.x + radius / 2, position.y + height,
                         position.z + radius / 2};

        // Raylib provides a helper
        return CheckCollisionBoxes(playerBox, box);
    }
};