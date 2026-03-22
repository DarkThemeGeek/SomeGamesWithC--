#pragma once
#include "Core/GameEngine.hpp"
#include <glm/vec2.hpp>
#include <iostream>

class FirstGame : GameEngine::Game {
  private:
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
        MainLoop(camera);
    };
    void run() {
        SetupCamera(camera);
        MainLoop(camera);
    }
    ~FirstGame() {};
};