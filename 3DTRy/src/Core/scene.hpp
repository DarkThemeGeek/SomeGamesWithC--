#pragma once
#include "glm/ext/vector_float3.hpp"
#include <raylib/raylib.h>
#include <string>
#include <unordered_map>
#include <vector>
namespace Engine {

class GameObject {
  public:
    virtual void update() {};
    virtual void draw() {};
    virtual ~GameObject() {};
};
class GameObjectMesh : public GameObject {
  public:
    Mesh mesh;
    Transform transform;

};
class Scene {
    std::pmr::vector<GameObject> gameObects;
};
} // namespace Engine