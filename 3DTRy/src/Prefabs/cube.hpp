#pragma once
#include <glm/ext/vector_float3.hpp>
#include <raylib/raylib.h>
struct Cube{
///x y z
glm::vec3 position;
///width height length
glm::vec3 size;
Color color;
//DrawCube( float width, float height, float length, Color color)4

virtual void Draw(){
    DrawCube({position.x,position.y,position.z}, size.x, size.y, size.z ,color);
    
}
};