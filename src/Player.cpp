#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Time.h"
#include "Player.h"

static bool firstMouse = true;
static f32 lastX = nanf("");
static f32 lastY = nanf("");

void Player::Update () {
    float velocity = this->speed * Time::deltaTime;

    glm::vec3 actualFront = glm::normalize(glm::vec3(this->camera.Front.x, 0, this->camera.Front.z));

    if (this->action_flags.run) velocity *= 2.0f;
    if (this->action_flags.forward) this->camera.Position += actualFront * velocity;
    if (this->action_flags.backward) this->camera.Position -= actualFront * velocity;
    if (this->action_flags.right) this->camera.Position += this->camera.Right * velocity;
    if (this->action_flags.left) this->camera.Position -= this->camera.Right * velocity;
    if (this->action_flags.up) this->camera.Position += glm::vec3(0, velocity, 0);
    if (this->action_flags.down) this->camera.Position -= glm::vec3(0, velocity, 0);

    this->camera.Update();
}



void Player::OnMouseMove (double xposd, double yposd) {
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

    this->camera.Pitch = glm::clamp(this->camera.Pitch + yoffset * this->mouseSensitivity, -89.0f, 89.0f);
    this->camera.Yaw += xoffset * this->mouseSensitivity;
}


void Player::OnResize (int width, int height) {
    this->camera.AspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

void Player::OnKeyPress (int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W) this->action_flags.forward = action == GLFW_PRESS;
    if (key == GLFW_KEY_S) this->action_flags.backward = action == GLFW_PRESS;
    if (key == GLFW_KEY_A) this->action_flags.left = action == GLFW_PRESS;
    if (key == GLFW_KEY_D) this->action_flags.right = action == GLFW_PRESS;
    if (key == GLFW_KEY_SPACE) this->action_flags.up = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_SHIFT) this->action_flags.down = action == GLFW_PRESS;
    if (key == GLFW_KEY_LEFT_CONTROL) this->action_flags.run = action == GLFW_PRESS;
}

void Player::OnMouseScroll (double xoffset, double yoffset) {
    this->camera.Zoom = glm::clamp(this->camera.Zoom - (float) yoffset, 1.0f, 45.0f);
}

