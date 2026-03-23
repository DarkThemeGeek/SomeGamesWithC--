#pragma once
#include "../../../include/raylib/raylib.h"
#include <raylib/raylib.h>
#include <string>
namespace GameEngine {
class Game {
  protected:
    int windowWidth, windowHeight;
    std::string title;
    int fps = 60;
    Camera3D camera{0};
    virtual void Init() { SetFps(fps); }
    virtual bool IsRunning() { return !WindowShouldClose(); }
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Shutdown() { CloseWindow(); }

  public:
    void SetFps(int fps) { this->fps = fps; };
    Game(int width, int height, std::string title);
    virtual ~Game() {};
    
    void MainLoop(Camera3D& camera);
};
} // namespace GameEngine