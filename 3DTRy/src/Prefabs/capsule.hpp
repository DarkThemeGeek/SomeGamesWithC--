#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::distance2
#include <raylib/raylib.h>

class Capsule {
  public:
    glm::vec3 position; // bottom of capsule
    float radius;
    float height;
    Color color;

    Capsule(glm::vec3 position, float radius, float height, Color color)
        : position(position), radius(radius), height(height), color(color) {}

    void Draw() {
        DrawCapsule({position.x, position.y, position.z},
                    {position.x, position.y + height, position.z}, radius, 6, 6,
                    color);
    }

    glm::vec3 Top() const { return position + glm::vec3(0.0f, height, 0.0f); }

    virtual ~Capsule() {}

  private:
    // Utility: closest point on segment ab to point p
    glm::vec3 ClosestPointOnSegment(const glm::vec3 &a, const glm::vec3 &b,
                                    const glm::vec3 &p) {
        glm::vec3 ab = b - a;
        float t = glm::dot(p - a, ab) / glm::dot(ab, ab);
        t = glm::clamp(t, 0.0f, 1.0f);
        return a + t * ab;
    }

  public:
    // Capsule vs Capsule collision
    bool CheckCollisionCapsuleCapsule(const Capsule &c1, const Capsule &c2) {
        glm::vec3 a1 = c1.position;
        glm::vec3 b1 = c1.Top();
        glm::vec3 a2 = c2.position;
        glm::vec3 b2 = c2.Top();

        // Get closest points between segments
        glm::vec3 p1 = ClosestPointOnSegment(a1, b1, a2);
        glm::vec3 p2 = ClosestPointOnSegment(a2, b2, p1);
        p1 = ClosestPointOnSegment(a1, b1, p2);

        float dist2 = glm::dot(p1 - p2, p1 - p2);
        float radiusSum = c1.radius + c2.radius;

        return dist2 <= radiusSum * radiusSum;
    }

    // Capsule vs Sphere collision
    bool CheckCollisionCapsuleSphere(const Capsule &c, const glm::vec3 &center,
                                     float sphereRadius) {
        glm::vec3 closest = ClosestPointOnSegment(c.position, c.Top(), center);
        float dist2 = glm::dot(closest - center, closest - center);
        float radiusSum = c.radius + sphereRadius;
        return dist2 <= radiusSum * radiusSum;
    }
  
};