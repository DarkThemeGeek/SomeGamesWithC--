#pragma once
#include "Core/GameEngine.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include "Prefabs/player.hpp"

class FirstGame : GameEngine::Game {
  private:
    Player player{glm::vec3(3.0f,1,-25),0.75,1,MAGENTA};
    bool IsRunning() override;
    void Update() override;
    void Draw() override;
    void Init() override;
    void Shutdown() override;
    void SetupCamera(Camera3D &camera);

  public:
    FirstGame(int width, int height, std::string title)
        : GameEngine::Game(width, height, title) {
        SetupCamera(camera);
       
    };
    void run() {
        SetupCamera(camera);
        MainLoop(camera);
    }
    ~FirstGame() {};
};