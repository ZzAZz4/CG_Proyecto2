

#ifndef OGL_RENDEROBJECTS_H
#define OGL_RENDEROBJECTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "types.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

static inline unsigned int cubeVAO = 0;
static inline unsigned int cubeVBO = 0;
static void renderCube () {
    // initialize (if necessary)
    if (cubeVAO == 0) {
        Vertex vertices[] = {
            // back face
            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +0.0f, +0.0f }}, // bottom-left
            {{ +0.5f, +0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +1.0f, +1.0f }}, // top-right
            {{ +0.5f, -0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +1.0f, +0.0f }}, // bottom-right
            {{ +0.5f, +0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +1.0f, +1.0f }}, // top-right
            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +0.0f, +0.0f }}, // bottom-left
            {{ -0.5f, +0.5f, -0.5f }, { +0.0f, +0.0f, -1.0f }, { +0.0f, +1.0f }}, // top-left
            // front face
            {{ -0.5f, -0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +0.0f, +0.0f }}, // bottom-left
            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +1.0f, +0.0f }}, // bottom-right
            {{ +0.5f, +0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +1.0f, +1.0f }}, // top-right
            {{ +0.5f, +0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +1.0f, +1.0f }}, // top-right
            {{ -0.5f, +0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +0.0f, +1.0f }}, // top-left
            {{ -0.5f, -0.5f, +0.5f }, { +0.0f, +0.0f, +1.0f }, { +0.0f, +0.0f }}, // bottom-left
            // left face
            {{ -0.5f, +0.5f, +0.5f }, { -1.0f, +0.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ -0.5f, +0.5f, -0.5f }, { -1.0f, +0.0f, +0.0f }, { +1.0f, +1.0f }},
            {{ -0.5f, -0.5f, -0.5f }, { -1.0f, +0.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ -0.5f, -0.5f, -0.5f }, { -1.0f, +0.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ -0.5f, -0.5f, +0.5f }, { -1.0f, +0.0f, +0.0f }, { +0.0f, +0.0f }},
            {{ -0.5f, +0.5f, +0.5f }, { -1.0f, +0.0f, +0.0f }, { +1.0f, +0.0f }},
            // right face
            {{ +0.5f, +0.5f, +0.5f }, { +1.0f, +0.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ +0.5f, -0.5f, -0.5f }, { +1.0f, +0.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, +0.5f, -0.5f }, { +1.0f, +0.0f, +0.0f }, { +1.0f, +1.0f }},
            {{ +0.5f, -0.5f, -0.5f }, { +1.0f, +0.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, +0.5f, +0.5f }, { +1.0f, +0.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ +0.5f, -0.5f, +0.5f }, { +1.0f, +0.0f, +0.0f }, { +0.0f, +0.0f }},
            // bottom face
            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +1.0f }},
            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ -0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +0.0f }},
            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +1.0f }},
            // top face
            {{ -0.5f, +0.5f, -0.5f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, +0.5f, +0.5f }, { +0.0f, +1.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ +0.5f, +0.5f, -0.5f }, { +0.0f, +1.0f, +0.0f }, { +1.0f, +1.0f }},
            {{ +0.5f, +0.5f, +0.5f }, { +0.0f, +1.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ -0.5f, +0.5f, -0.5f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ -0.5f, +0.5f, +0.5f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +0.0f }},
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (offsetof(Vertex, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (offsetof(Vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (offsetof(Vertex, texCoords)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


static inline unsigned int pyramidVAO = 0;
static inline unsigned int pyramidVBO = 0;
static inline void renderPyramid () {
    if (pyramidVAO == 0) {

        Vertex vertices[] = {
            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, +0.5f, +1.0f }, { +0.0f, +0.0f }},
            {{ +0.0f, +0.5f, +0.0f }, { +0.0f, +0.5f, +1.0f }, { +0.0f, +1.0f }},
            {{ -0.5f, -0.5f, +0.5f }, { +0.0f, +0.5f, +1.0f }, { +1.0f, +0.0f }},

            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, +0.5f, -1.0f }, { +0.0f, +0.0f }},
            {{ +0.0f, +0.5f, +0.0f }, { +0.0f, +0.5f, -1.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, -0.5f, -0.5f }, { +0.0f, +0.5f, -1.0f }, { +1.0f, +0.0f }},

            {{ -0.5f, -0.5f, +0.5f }, { -1.0f, +0.5f, +0.0f }, { +0.0f, +0.0f }},
            {{ +0.0f, +0.5f, +0.0f }, { -1.0f, +0.5f, +0.0f }, { +0.0f, +1.0f }},
            {{ -0.5f, -0.5f, -0.5f }, { -1.0f, +0.5f, +0.0f }, { +1.0f, +0.0f }},

            {{ +0.5f, -0.5f, -0.5f }, { +1.0f, +0.5f, +0.0f }, { +0.0f, +0.0f }},
            {{ +0.0f, +0.5f, +0.0f }, { +1.0f, +0.5f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, -0.5f, +0.5f }, { +1.0f, +0.5f, +0.0f }, { +1.0f, +0.0f }},

            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +1.0f }},
            {{ +0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +1.0f }},
            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +0.0f }},

            {{ +0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +1.0f, +0.0f }},
            {{ -0.5f, -0.5f, +0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +0.0f }},
            {{ -0.5f, -0.5f, -0.5f }, { +0.0f, -1.0f, +0.0f }, { +0.0f, +1.0f }},
        };

        glGenVertexArrays(1, &pyramidVAO);
        glGenBuffers(1, &pyramidVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(pyramidVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*) (offsetof(Vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, texCoords)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Pyramid
    glBindVertexArray(pyramidVAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}


static inline unsigned int planeVAO;
static inline unsigned int planeVBO;
static void renderPlane () {
    if (!planeVAO) {
        const Vertex planeVertices[] = {
            {{ -1.0f, -0.f, -1.0f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +25.0f }},
            {{ -1.0f, -0.f, +1.0f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +0.0f }},
            {{ +1.0f, -0.f, +1.0f }, { +0.0f, +1.0f, +0.0f }, { +25.0f, +0.0f }},

            {{ -1.0f, -0.0f, -1.0f }, { +0.0f, +1.0f, +0.0f }, { +0.0f, +25.0f }},
            {{ +1.0f, -0.0f, +1.0f }, { +0.0f, +1.0f, +0.0f }, { +25.0f, +0.0f }},
            {{ +1.0f, -0.0f, -1.0f }, { +0.0f, +1.0f, +0.0f }, { +25.0f, +25.0f }},
        };
        // plane VAO

        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, texCoords)));
        glBindVertexArray(0);
    }
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}


#endif //OGL_RENDEROBJECTS_H
