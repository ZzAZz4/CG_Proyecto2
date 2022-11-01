
#include "PlayerPhysics.h"

glm::vec3 PlayerPhysics::offsetedPosition(const Player& player, const World& world,
                                          const glm::vec3& posOffset, float velocity) {
    if (posOffset == glm::vec3(0, 0, 0)) {
        return player.camera.Position;
    }

    glm::vec3 newPosition = player.camera.Position + posOffset;
    uint8_t block = world.GetBlock(newPosition.x, newPosition.y, newPosition.z);

    // TODO: Dejar al jugador justo antes de chocar con el bloque

    if (block != Block::Air) {
        glm::vec3 dir = player.camera.Right * velocity;
        dir = glm::vec3(dir.z, dir.y, dir.x);
        if (player.action_flags.forward || player.action_flags.right) {
            return player.camera.Position + dir;
        }
        if (player.action_flags.backward || player.action_flags.left) {
            return player.camera.Position - dir;
        }
    } else {
        return newPosition;
    }
}
