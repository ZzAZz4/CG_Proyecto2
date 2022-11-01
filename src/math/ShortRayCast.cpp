

#include "ShortRayCast.h"
#include "../game/Block.h"

static float nextAxisHit(const glm::vec3& origin, const glm::vec3& dir, float currentTime) {
    glm::vec3 pos = origin + dir * (currentTime);

    int nextX = dir.x > 0 ? floor(pos.x) + 1 : ceil(pos.x) - 1;
    int nextY = dir.y > 0 ? floor(pos.y) + 1 : ceil(pos.y) - 1;
    int nextZ = dir.z > 0 ? floor(pos.z) + 1 : ceil(pos.z) - 1;

    float nextXTime = ((float)nextX - pos.x) / dir.x;
    float nextYTime = ((float)nextY - pos.y) / dir.y;
    float nextZTime = ((float)nextZ - pos.z) / dir.z;

    return currentTime + std::min(std::min(nextXTime, nextYTime), nextZTime);
}

ShortRayCast::ShortRayCast(const glm::vec3& start, const glm::vec3& dir, float max_distance) {
    this->start = start;
    this->dir = glm::normalize(dir);
    this->max_distance = max_distance;
}

float ShortRayCast::Hit(const World* world) const {

    for (float time = 0.0f; time < max_distance;) {
        glm::ivec3 pos = glm::ivec3(start + dir * time);

        if (world->GetBlock((int)pos.x, (int)pos.y, (int)pos.z) != Block::Air) {
            return time;
        }
        time = nextAxisHit(pos, dir, time);
    }
    return -1.0f;
}

float ShortRayCast::BeforeHit(const World* world) const {
    float past_time = 0.0f;
    for (float time = 0.0f; time < max_distance;) {
        glm::ivec3 pos = glm::ivec3(start + dir * time);

        if (world->GetBlock((int)pos.x, (int)pos.y, (int)pos.z) != Block::Air) {
            printf("past_time: %f, time: %f\n", past_time, time);
            printf("past_block: %d, block: %d\n",
                   world->GetBlock((int)(start + dir * past_time).x,
                                   (int)(start + dir * past_time).y,
                                   (int)(start + dir * past_time).z),
                   world->GetBlock((int)pos.x, (int)pos.y, (int)pos.z));
            return past_time;
        }
        past_time = time;
        time = nextAxisHit(pos, dir, time);
    }
    return -1.0f;
}
