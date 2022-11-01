

#ifndef OGL_SHORTRAYCAST_H
#define OGL_SHORTRAYCAST_H

#include "../game/World.h"
#include <optional>

struct ShortRayCast {
    glm::vec3 start;
    glm::vec3 dir;
    float max_distance;

    ShortRayCast(const glm::vec3& start, const glm::vec3& dir, float max_distance);
    float Hit(const World* world) const;
    float BeforeHit(const World* world) const;
};

#endif // OGL_SHORTRAYCAST_H
