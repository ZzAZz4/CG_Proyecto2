
#include "Chunk.h"
#include "Block.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

using byte4 = glm::tvec4<uint8_t>;

byte4 vertex[Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::MAX_HEIGHT * 6 * 6];

Chunk::Chunk() : blocks{}, VAO(0), VBO(0), elements(0), needs_update(true) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                blocks[x][y][z] = Block::Air;
            }
        }
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // allocate space for the buffer
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(blocks), nullptr, GL_DYNAMIC_DRAW);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, sizeof(byte4), (void*)(0));
}

uint8_t Chunk::GetBlock(int x, int y, int z) const { return blocks[x][y][z]; }

void Chunk::SetBlock(int x, int y, int z, uint8_t block) {
    blocks[x][y][z] = block;
    needs_update = true;
}

Chunk::~Chunk() { glDeleteBuffers(1, &VBO); }

void Chunk::Update() {
    if (!needs_update)
        return;
    needs_update = false;

    int i = 0;
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                auto block = GetBlock(x, y, z);
                if (block == Block::Air) {
                    continue;
                }

                if (x == 0 || GetBlock(x - 1, y, z) == Block::Air) {
                    vertex[i++] = {x, y, z, block};
                    vertex[i++] = {x, y + 1, z, block};
                    vertex[i++] = {x, y, z + 1, block};
                    vertex[i++] = {x, y, z + 1, block};
                    vertex[i++] = {x, y + 1, z, block};
                    vertex[i++] = {x, y + 1, z + 1, block};
                }
                if (x + 1 == CHUNK_SIZE || GetBlock(x + 1, y, z) == Block::Air) {
                    vertex[i++] = {x + 1, y, z, block};
                    vertex[i++] = {x + 1, y, z + 1, block};
                    vertex[i++] = {x + 1, y + 1, z, block};
                    vertex[i++] = {x + 1, y + 1, z, block};
                    vertex[i++] = {x + 1, y, z + 1, block};
                    vertex[i++] = {x + 1, y + 1, z + 1, block};
                }
                if (y == 0 || GetBlock(x, y - 1, z) == Block::Air) {
                    vertex[i++] = {x, y, z, -block};
                    vertex[i++] = {x, y, z + 1, -block};
                    vertex[i++] = {x + 1, y, z, -block};
                    vertex[i++] = {x + 1, y, z, -block};
                    vertex[i++] = {x, y, z + 1, -block};
                    vertex[i++] = {x + 1, y, z + 1, -block};
                }
                if (y + 1 == MAX_HEIGHT || GetBlock(x, y + 1, z) == Block::Air) {
                    vertex[i++] = {x, y + 1, z, -block};
                    vertex[i++] = {x + 1, y + 1, z, -block};
                    vertex[i++] = {x, y + 1, z + 1, -block};
                    vertex[i++] = {x + 1, y + 1, z, -block};
                    vertex[i++] = {x + 1, y + 1, z + 1, -block};
                    vertex[i++] = {x, y + 1, z + 1, -block};
                }
                if (z == 0 || GetBlock(x, y, z - 1) == Block::Air) {
                    vertex[i++] = {x, y, z, block};
                    vertex[i++] = {x + 1, y, z, block};
                    vertex[i++] = {x, y + 1, z, block};
                    vertex[i++] = {x + 1, y, z, block};
                    vertex[i++] = {x + 1, y + 1, z, block};
                    vertex[i++] = {x, y + 1, z, block};
                }
                if (z + 1 == CHUNK_SIZE || GetBlock(x, y, z + 1) == Block::Air) {
                    vertex[i++] = {x, y, z + 1, block};
                    vertex[i++] = {x, y + 1, z + 1, block};
                    vertex[i++] = {x + 1, y, z + 1, block};
                    vertex[i++] = {x + 1, y, z + 1, block};
                    vertex[i++] = {x, y + 1, z + 1, block};
                    vertex[i++] = {x + 1, y + 1, z + 1, block};
                }
            }
        }
    }
    elements = i;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, elements * (int)sizeof(byte4), vertex);
}

void Chunk::Render() {
    if (elements == 0) {
        return;
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, elements);
}
