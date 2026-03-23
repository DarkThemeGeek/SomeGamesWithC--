#pragma once
#include "capsule.hpp"
#include "raylib/raylib.h"
#include <glm/ext/vector_float3.hpp>
class Player:public Capsule{
public:
  Player(glm::vec3 position, float radius,float height,Color color):Capsule(position,  radius, height,  color){}
  void Draw(){
    Capsule::Draw();
  }
  void Walk(){
    position+=speed*GetFrameTime();
  }
  glm::vec3 speed;
  
};