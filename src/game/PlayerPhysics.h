

#ifndef OGL_PLAYERPHYSICS_H
#define OGL_PLAYERPHYSICS_H

#include "Player.h"
#include "World.h"
#include <glm/glm.hpp>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;

    AABB operator+(const glm::vec3& vec) const { return {min + vec, max + vec}; }
};

namespace PlayerPhysics {
    static inline const AABB playerAABB = {glm::vec3(-0.3f, -1.6f, -0.3f),
                                           glm::vec3(0.3f, 0.2f, 0.3f)};

    glm::vec3 result(Player& player, const World& world, const glm::vec3& posOffset);
}; // namespace PlayerPhysics

#endif // OGL_PLAYERPHYSICS_H
