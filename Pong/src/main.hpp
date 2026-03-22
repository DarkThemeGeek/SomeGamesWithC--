#pragma once
#include "Core/GameEngine.hpp"
#include "Prefabs/block.hpp"
#include <glm/vec2.hpp>
#include <iostream>

class FirstGame : GameEngine::Game {
  private:
    Rectangle rect{0, windowHeight * 3.0f / 4.0f, 80, 20};
    struct Circle {
        glm::vec2 centre{};
        int radius = 5;
        glm::vec2 velocity{-120, -120};
    } circle;

    bool intersects(Circle circle, Rectangle rect) const;
    glm::vec2 GetNormal( Circle& circle,const Rectangle& rect);

    bool IsRunning() override;
    void Update() override;
    void Draw() override;
    void Init() override;
    void Shutdown() override;

    void HandleCollisons();
    
    bool GameOver = false;

    Block blocks[14][10];

  public:
    FirstGame(int width, int height, std::string title)
        : GameEngine::Game(width, height, title) {
        circle.centre.y=450;
        circle.centre.x=400;
        MainLoop();
    };
    ~FirstGame() {};
    
};