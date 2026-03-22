#pragma once
#include"../../include/raylib/raylib.h"
namespace UI {
class Button {
  public:
    int width,height;
    int x,y;
    Color color;
    void DrawButton();
    Button(int x,int y,int width,int height,Color color):x(x),y(y),width(width),height(height){};
    ~Button(){};
    
};
} // namespace UI