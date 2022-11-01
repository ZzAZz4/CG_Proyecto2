

#ifndef OGL_PLAYERPHYSICS_H
#define OGL_PLAYERPHYSICS_H

#include <glm/glm.hpp>
#include "World.h"
#include "Player.h"

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

namespace PlayerPhysics {
    const AABB playerAABB = {
        glm::vec3(-0.3f, -1.6f, -0.3f),
        glm::vec3(0.3f, 0.2f, 0.3f)
    };
    glm::vec3 offsetedPosition(const Player& player, const World& world, const glm::vec3& posOffset, float velocity);
};

#endif // OGL_PLAYERPHYSICS_H
