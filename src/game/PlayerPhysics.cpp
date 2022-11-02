
#include "PlayerPhysics.h"

bool collidesWithBlock(const World& world, const glm::vec3& pos) {
    glm::ivec3 blockPos = pos;
    auto block = world.GetBlock(blockPos.x, blockPos.y, blockPos.z);
    return Block::data[block].collisionAmortization == 0;
}

bool createsXPositiveCollision(const AABB& aabb, float x_dir, const World& world) {
    glm::vec3 pos_front_top_right = glm::vec3(aabb.max.x + x_dir, aabb.max.y, aabb.max.z);
    glm::vec3 pos_front_bottom_right = glm::vec3(aabb.max.x + x_dir, aabb.min.y, aabb.max.z);
    glm::vec3 pos_back_top_right = glm::vec3(aabb.max.x + x_dir, aabb.max.y, aabb.min.z);
    glm::vec3 pos_back_bottom_right = glm::vec3(aabb.max.x + x_dir, aabb.min.y, aabb.min.z);

    if (collidesWithBlock(world, pos_front_top_right))
        return true;
    if (collidesWithBlock(world, pos_front_bottom_right))
        return true;
    if (collidesWithBlock(world, pos_back_top_right))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_right))
        return true;
    return false;
}

bool createsXNegativeCollision(const AABB& aabb, float x_dir, const World& world) {
    glm::vec3 pos_front_top_left = glm::vec3(aabb.min.x + x_dir, aabb.max.y, aabb.max.z);
    glm::vec3 pos_front_bottom_left = glm::vec3(aabb.min.x + x_dir, aabb.min.y, aabb.max.z);
    glm::vec3 pos_back_top_left = glm::vec3(aabb.min.x + x_dir, aabb.max.y, aabb.min.z);
    glm::vec3 pos_back_bottom_left = glm::vec3(aabb.min.x + x_dir, aabb.min.y, aabb.min.z);

    if (collidesWithBlock(world, pos_front_top_left))
        return true;
    if (collidesWithBlock(world, pos_front_bottom_left))
        return true;
    if (collidesWithBlock(world, pos_back_top_left))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_left))
        return true;
    return false;
}

bool createsYPositiveCollision(const AABB& aabb, float y_dir, const World& world) {
    glm::vec3 pos_front_top_left = glm::vec3(aabb.min.x, aabb.max.y + y_dir, aabb.max.z);
    glm::vec3 pos_front_top_right = glm::vec3(aabb.max.x, aabb.max.y + y_dir, aabb.max.z);
    glm::vec3 pos_back_top_left = glm::vec3(aabb.min.x, aabb.max.y + y_dir, aabb.min.z);
    glm::vec3 pos_back_top_right = glm::vec3(aabb.max.x, aabb.max.y + y_dir, aabb.min.z);

    if (collidesWithBlock(world, pos_front_top_left))
        return true;
    if (collidesWithBlock(world, pos_front_top_right))
        return true;
    if (collidesWithBlock(world, pos_back_top_left))
        return true;
    if (collidesWithBlock(world, pos_back_top_right))
        return true;
    return false;
}

bool createsYNegativeCollision(const AABB& aabb, float y_dir, const World& world) {
    glm::vec3 pos_front_bottom_left = glm::vec3(aabb.min.x, aabb.min.y + y_dir, aabb.max.z);
    glm::vec3 pos_front_bottom_right = glm::vec3(aabb.max.x, aabb.min.y + y_dir, aabb.max.z);
    glm::vec3 pos_back_bottom_left = glm::vec3(aabb.min.x, aabb.min.y + y_dir, aabb.min.z);
    glm::vec3 pos_back_bottom_right = glm::vec3(aabb.max.x, aabb.min.y + y_dir, aabb.min.z);

    if (collidesWithBlock(world, pos_front_bottom_left))
        return true;
    if (collidesWithBlock(world, pos_front_bottom_right))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_left))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_right))
        return true;
    return false;
}

bool createsZPositiveCollision(const AABB& aabb, float z_dir, const World& world) {
    glm::vec3 pos_front_top_left = glm::vec3(aabb.min.x, aabb.max.y, aabb.max.z + z_dir);
    glm::vec3 pos_front_top_right = glm::vec3(aabb.max.x, aabb.max.y, aabb.max.z + z_dir);
    glm::vec3 pos_front_bottom_left = glm::vec3(aabb.min.x, aabb.min.y, aabb.max.z + z_dir);
    glm::vec3 pos_front_bottom_right = glm::vec3(aabb.max.x, aabb.min.y, aabb.max.z + z_dir);

    if (collidesWithBlock(world, pos_front_top_left))
        return true;
    if (collidesWithBlock(world, pos_front_top_right))
        return true;
    if (collidesWithBlock(world, pos_front_bottom_left))
        return true;
    if (collidesWithBlock(world, pos_front_bottom_right))
        return true;
    return false;
}

bool createsZNegativeCollision(const AABB& aabb, float z_dir, const World& world) {
    glm::vec3 pos_back_top_left = glm::vec3(aabb.min.x, aabb.max.y, aabb.min.z + z_dir);
    glm::vec3 pos_back_top_right = glm::vec3(aabb.max.x, aabb.max.y, aabb.min.z + z_dir);
    glm::vec3 pos_back_bottom_left = glm::vec3(aabb.min.x, aabb.min.y, aabb.min.z + z_dir);
    glm::vec3 pos_back_bottom_right = glm::vec3(aabb.max.x, aabb.min.y, aabb.min.z + z_dir);

    if (collidesWithBlock(world, pos_back_top_left))
        return true;
    if (collidesWithBlock(world, pos_back_top_right))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_left))
        return true;
    if (collidesWithBlock(world, pos_back_bottom_right))
        return true;
    return false;
}

static float CalculateAmortization(const AABB& aabb, const World& world, bool& canSwim) {
    glm::vec3 pos_back_top_left = glm::vec3(aabb.min.x, aabb.max.y, aabb.min.z);
    glm::vec3 pos_back_top_right = glm::vec3(aabb.max.x, aabb.max.y, aabb.min.z);
    glm::vec3 pos_back_bottom_left = glm::vec3(aabb.min.x, aabb.min.y, aabb.min.z);
    glm::vec3 pos_back_bottom_right = glm::vec3(aabb.max.x, aabb.min.y, aabb.min.z);
    glm::vec3 pos_front_top_left = glm::vec3(aabb.min.x, aabb.max.y, aabb.max.z);
    glm::vec3 pos_front_top_right = glm::vec3(aabb.max.x, aabb.max.y, aabb.max.z);
    glm::vec3 pos_front_bottom_left = glm::vec3(aabb.min.x, aabb.min.y, aabb.max.z);
    glm::vec3 pos_front_bottom_right = glm::vec3(aabb.max.x, aabb.min.y, aabb.max.z);

    auto block_back_top_left = world.GetBlock(pos_back_top_left.x, pos_back_top_left.y, pos_back_top_left.z);
    auto block_back_top_right = world.GetBlock(pos_back_top_right.x, pos_back_top_right.y, pos_back_top_right.z);
    auto block_back_bottom_left = world.GetBlock(pos_back_bottom_left.x, pos_back_bottom_left.y, pos_back_bottom_left.z);
    auto block_back_bottom_right = world.GetBlock(pos_back_bottom_right.x, pos_back_bottom_right.y, pos_back_bottom_right.z);
    auto block_front_top_left = world.GetBlock(pos_front_top_left.x, pos_front_top_left.y, pos_front_top_left.z);
    auto block_front_top_right = world.GetBlock(pos_front_top_right.x, pos_front_top_right.y, pos_front_top_right.z);
    auto block_front_bottom_left = world.GetBlock(pos_front_bottom_left.x, pos_front_bottom_left.y, pos_front_bottom_left.z);
    auto block_front_bottom_right = world.GetBlock(pos_front_bottom_right.x, pos_front_bottom_right.y, pos_front_bottom_right.z);

    if (block_back_top_left == Block::Water || block_back_top_right == Block::Water || block_back_bottom_left == Block::Water || block_back_bottom_right == Block::Water ||
        block_front_top_left == Block::Water || block_front_top_right == Block::Water || block_front_bottom_left == Block::Water || block_front_bottom_right == Block::Water) {
        canSwim = true;
    } else {
        canSwim = false;
    }

    auto a1 = Block::data[block_back_top_left].collisionAmortization;
    auto a2 = Block::data[block_back_top_right].collisionAmortization;
    auto a3 = Block::data[block_back_bottom_left].collisionAmortization;
    auto a4 = Block::data[block_back_bottom_right].collisionAmortization;
    auto a5 = Block::data[block_front_top_left].collisionAmortization;
    auto a6 = Block::data[block_front_top_right].collisionAmortization;
    auto a7 = Block::data[block_front_bottom_left].collisionAmortization;
    auto a8 = Block::data[block_front_bottom_right].collisionAmortization;

    return glm::min(glm::min(glm::min(glm::min(glm::min(glm::min(glm::min(a1, a2), a3), a4), a5), a6), a7), a8);
}

glm::vec3 PlayerPhysics::result(Player& player, const World& world, const glm::vec3& posOffset) {
    glm::vec3 final_direction(0.0f);

    float posOffsetX = posOffset.x;
    float posOffsetY = posOffset.y;
    float posOffsetZ = posOffset.z;

    const auto aabb = playerAABB + player.camera.Position;

    if (posOffsetX > 0.0f && !createsXPositiveCollision(aabb, posOffsetX, world)) {
        final_direction.x = posOffsetX;
    } else if (posOffsetX < 0.0f && !createsXNegativeCollision(aabb, posOffsetX, world)) {
        final_direction.x = posOffsetX;
    }

    if (posOffsetY > 0.0f && !createsYPositiveCollision(aabb, posOffsetY, world)) {
        final_direction.y = posOffsetY;
    } else if (createsYNegativeCollision(aabb, posOffsetY, world)) {
        player.touchesGround = true;
    } else {
        player.touchesGround = false;
        final_direction.y = posOffsetY;
    }

    if (posOffsetZ > 0.0f && !createsZPositiveCollision(aabb, posOffsetZ, world)) {
        final_direction.z = posOffsetZ;
    } else if (posOffsetZ < 0.0f && !createsZNegativeCollision(aabb, posOffsetZ, world)) {
        final_direction.z = posOffsetZ;
    }

    float amortization = CalculateAmortization(aabb, world, player.canSwim);
    if (amortization == 0.0f) {
        return player.camera.Position + final_direction;
    }
    return player.camera.Position + final_direction * amortization;
}
