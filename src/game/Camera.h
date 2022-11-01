#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles,
// Vectors and Matrices for use in OpenGL
class Camera {
public:
    glm::mat4 Projection{};
    glm::mat4 View{};

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;

    float Yaw;
    float Pitch;
    float Zoom;
    float AspectRatio = nanf("");

    // constructor with vectors
    Camera(const glm::vec3& position, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM) {
        Position = position;
        Yaw = yaw;
        Pitch = pitch;
    }
    void Update() {
        RecalculateProjection();
        RecalculateView();
    }

private:
    void RecalculateProjection() {
        Projection = glm::perspective(glm::radians(Zoom), this->AspectRatio, 0.1f, 100.0f);
    }

    void RecalculateView() {
        glm::vec3 front;
        front.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
        front.y = glm::sin(glm::radians(Pitch));
        front.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));

        Front = glm::normalize(front);
        View = glm::lookAt(Position, Position + Front, glm::vec3(0.0f, 1.0f, 0.0f));
        Right = glm::normalize(glm::vec3(View[0][0], View[1][0], View[2][0]));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif