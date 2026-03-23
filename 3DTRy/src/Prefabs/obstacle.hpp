#pragma once
#include "cube.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float3.hpp"
#include "raylib/raylib.h"
class Obstacle: public Cube{
float speed;
public:
void Move(){
    position+=glm::vec3{0,0,-speed}*GetFrameTime();
}
bool spawned;
Obstacle(const glm::vec3& position,const glm::vec3& size,const Color& color,int speed){
    this->position=position;
    this->size=size;
    this->color=color;
    this->speed=speed;
    spawned=true;

}

virtual ~Obstacle(){};
};