#include "Player.h"
#include "../math/ShortRayCast.h"
#include "PlayerPhysics.h"
#include "Time.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>

static bool firstMouse = true;
static float lastX = nanf("");
static float lastY = nanf("");

static glm::vec3 spawnPosition(World* world) {
    return {World::DIAMETER_X / 2,
            world->GetHeightAt(World::DIAMETER_X / 2, World::DIAMETER_Z / 2) + 2,
            World::DIAMETER_Z / 2};
}

Player::Player(World* world)
    : camera(spawnPosition(world), 90.f, 0.f), world(world) {}

void Player::Update() {
    float velocity = (this->actionFlags.run ? this->runSpeed : this->speed) * Time::deltaTime;

    glm::vec3 posOffset = glm::vec3(0, 0, 0);
    glm::vec3 flatFront = glm::normalize(glm::vec3(this->camera.Front.x, 0, this->camera.Front.z));

    if (this->actionFlags.forward)
        posOffset += flatFront * velocity;
    if (this->actionFlags.backward)
        posOffset -= flatFront * velocity;
    if (this->actionFlags.right)
        posOffset += this->camera.Right * velocity;
    if (this->actionFlags.left)
        posOffset -= this->camera.Right * velocity;
    if (this->actionFlags.up) {
        if (!inSurvival || this->canSwim) {
            posOffset += glm::vec3(0, velocity, 0);
        } else if (touchesGround) {
            touchesGround = false;
            this->yAddedVelocity = this->impulse;
        }
    }
    if (this->actionFlags.down) {
        if (!inSurvival) {
            posOffset -= glm::vec3(0, velocity, 0);
        }
    }

    if (inSurvival) {
        yAddedVelocity =
            touchesGround ? -0.01f
                          : glm::clamp(yAddedVelocity + gravity * Time::deltaTime, -30.0f, 30.0f);
        posOffset.y += yAddedVelocity * Time::deltaTime;
        this->camera.Position = PlayerPhysics::result(*this, *this->world, posOffset);
    } else {
        touchesGround = false;
        yAddedVelocity = 0;
        this->camera.Position += posOffset;
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
        this->actionFlags.forward = action == GLFW_PRESS;
    if (key == GLFW_KEY_S)
        this->actionFlags.backward = action == GLFW_PRESS;
    if (key == GLFW_KEY_A)
        this->actionFlags.left = action == GLFW_PRESS;
    if (key == GLFW_KEY_D)
        this->actionFlags.right = action == GLFW_PRESS;
    if (key == GLFW_KEY_SPACE)
        this->actionFlags.up = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
        this->actionFlags.down = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
        this->actionFlags.run = action == GLFW_PRESS;
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

void Player::Respawn() { this->camera.Position = spawnPosition(this->world) + glm::vec3(0, 3, 0); }

void Player::Dump(std::ofstream& ofstream) {
    ofstream.write(reinterpret_cast<char*>(&this->camera.Position), sizeof(glm::vec3));
    ofstream.write(reinterpret_cast<char*>(&this->camera.Yaw), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->camera.Pitch), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->heldBlock), sizeof(Block));
    ofstream.write(reinterpret_cast<char*>(&this->inSurvival), sizeof(bool));

    ofstream.write(reinterpret_cast<char*>(&this->speed), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->runSpeed), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->mouseSensitivity), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->impulse), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->gravity), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->yAddedVelocity), sizeof(float));
    ofstream.write(reinterpret_cast<char*>(&this->touchesGround), sizeof(bool));

}
void Player::Load(std::ifstream& ifstream) {
    ifstream.read(reinterpret_cast<char*>(&this->camera.Position), sizeof(glm::vec3));
    ifstream.read(reinterpret_cast<char*>(&this->camera.Yaw), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->camera.Pitch), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->heldBlock), sizeof(Block));
    ifstream.read(reinterpret_cast<char*>(&this->inSurvival), sizeof(bool));

    ifstream.read(reinterpret_cast<char*>(&this->speed), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->runSpeed), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->mouseSensitivity), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->impulse), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->gravity), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->yAddedVelocity), sizeof(float));
    ifstream.read(reinterpret_cast<char*>(&this->touchesGround), sizeof(bool));

    printf("Camera: %f %f %f\n", this->camera.Front.x, this->camera.Front.y, this->camera.Front.z);
    printf("Angles: %f %f\n", this->camera.Yaw, this->camera.Pitch);
    printf("Held block: %d\n", this->heldBlock);
    printf("In survival: %d\n", this->inSurvival);

    printf("Settings: %f %f %f %f %f %f %d\n", this->speed, this->runSpeed, this->mouseSensitivity, this->impulse, this->gravity, this->yAddedVelocity, this->touchesGround);

    Update();
}
