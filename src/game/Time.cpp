#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Time.h"

void Time::Init () {
    lastFrame = (float) glfwGetTime();
}
void Time::Update () {
    auto currentFrame = (float) glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
float Time::GetFPS () {
    return 1.0f / deltaTime;
}

