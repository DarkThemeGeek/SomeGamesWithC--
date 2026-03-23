#pragma once
#include "Core/GameEngine.hpp"
#include "Prefabs/obstacle.hpp"
#include "Prefabs/player.hpp"
#include "raylib/raylib.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <vector>
BoundingBox ToBoundingBox(const glm::vec3 &vec, const glm::vec3 &size);
Vector3 ToVec3(glm::vec3 &vec);

class FirstGame : GameEngine::Game {
  private:
   
    //Default player a capsule with collisons
    Player player{glm::vec3(3.0f, 1, -25), 0.75, 1, MAGENTA};
    //Obstacle buffer
    std::vector<Obstacle> obstacles;
    //player speed var
    int PlayerSpeed = 10;
    //vars to be used to express lains x is the coord for lains
    enum Lains { Lain1X = 1, Lain2X = 3, Lain3X = 5 };
    // Gameplay systems
    void Movement(float dt);
    void CheckCollisons();
    void SetupCamera(Camera3D &camera);
    // Inherited functions from game engine
    bool IsRunning() override;
    void Update(float dt) override;
    void Draw() override;
    void Init() override;
    void Shutdown() override;
    //Button Layout
    enum Buttons{
      jump=KEY_SPACE
    };
  public:
    FirstGame(int width, int height, std::string title)
        : GameEngine::Game(width, height, title) {
        SetupCamera(camera);
    };
    //function to run the game
    void run() {
        SetupCamera(camera);
        MainLoop(camera);
    }
    ~FirstGame() {

    };
};