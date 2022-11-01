#include "Player.h"
#include "../math/ShortRayCast.h"
#include "Time.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stdio.h>

static bool firstMouse = true;
static float lastX = nanf("");
static float lastY = nanf("");

Player::Player(World* world, PlayerSettings settings)
    : world(world), speed(settings.speed), mouseSensitivity(settings.mouseSensitivity) {}

void Player::Update() {
    float velocity = this->speed * Time::deltaTime;

    glm::vec3 posOffset = glm::vec3(0, 0, 0);
    glm::vec3 actualFront =
        glm::normalize(glm::vec3(this->camera.Front.x, 0, this->camera.Front.z));

    if (this->action_flags.run)
        velocity *= 2.0f;
    if (this->action_flags.forward)
        posOffset += actualFront * velocity;
    if (this->action_flags.backward)
        posOffset -= actualFront * velocity;
    if (this->action_flags.right)
        posOffset += this->camera.Right * velocity;
    if (this->action_flags.left)
        posOffset -= this->camera.Right * velocity;
    if (this->action_flags.up)
        posOffset += glm::vec3(0, velocity, 0);
    if (this->action_flags.down)
        posOffset -= glm::vec3(0, velocity, 0);

    if (inSurvival) {
        if (posOffset != glm::vec3(0, 0, 0)) {
            glm::vec3 newPosition = this->camera.Position + posOffset;
            uint8_t block = world->GetBlock(newPosition.x, newPosition.y, newPosition.z);

            // TODO: Dejar al jugador justo antes de chocar con el bloque

            if (block != Block::Air) {
                glm::vec3 dir = this->camera.Right * velocity;
                dir = glm::vec3(dir.z, dir.y, dir.x);
                if (this->action_flags.forward || this->action_flags.right)
                    this->camera.Position += dir;
                if (this->action_flags.backward || this->action_flags.left)
                    this->camera.Position -= dir;
            } else {
                this->camera.Position = newPosition;
            }
        }
    }


    this->camera.Update();
}

void Player::OnMouseMove(double xposd, double yposd) {
    auto xpos = static_cast<float>(xposd);
    auto ypos = static_cast<float>(yposd);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    this->camera.Pitch =
        glm::clamp(this->camera.Pitch + yoffset * this->mouseSensitivity, -89.0f, 89.0f);
    this->camera.Yaw += xoffset * this->mouseSensitivity;
}

void Player::OnResize(int width, int height) {
    this->camera.AspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

void Player::OnKeyPress(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W)
        this->action_flags.forward = action == GLFW_PRESS;
    if (key == GLFW_KEY_S)
        this->action_flags.backward = action == GLFW_PRESS;
    if (key == GLFW_KEY_A)
        this->action_flags.left = action == GLFW_PRESS;
    if (key == GLFW_KEY_D)
        this->action_flags.right = action == GLFW_PRESS;
    if (key == GLFW_KEY_SPACE)
        this->action_flags.up = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
        this->action_flags.down = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
        this->action_flags.run = action == GLFW_PRESS;
}

void Player::OnMouseScroll(double xoffset, double yoffset) {
    this->camera.Zoom = glm::clamp(this->camera.Zoom - (float)yoffset, 1.0f, 45.0f);
}

void Player::OnMouseClick(int button, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }

    ShortRayCast rayCast{this->camera.Position, this->camera.Front, 6.0f};
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (const float hit = rayCast.Hit(world); hit != -1.0f) {
            const glm::ivec3 res = this->camera.Position + (this->camera.Front * hit);
            world->SetBlock(res.x, res.y, res.z, Block::Air);
        }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (const float hit = rayCast.BeforeHit(world); hit != -1.0f) {
            glm::ivec3 res = this->camera.Position + (this->camera.Front * hit);
            world->SetBlock(res.x, res.y, res.z, this->heldBlock);
        }
    }
}
