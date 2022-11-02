
#include "Chunk.h"
#include "Block.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

using byte4 = glm::tvec4<uint8_t>;

struct ChunkVertex {
    byte4 position;
    uint8_t normal;
};

ChunkVertex vertex[Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::MAX_HEIGHT * 6 * 6];

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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, sizeof(ChunkVertex), (void*)(offsetof(ChunkVertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, sizeof(ChunkVertex), (void*)(offsetof(ChunkVertex, normal)));
}

uint8_t Chunk::GetBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}

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
                    vertex[i++] = {{x, y, z, block}, (1 << 1) + 0};
                    vertex[i++] = {{x, y + 1, z, block}, (1 << 1) + 0};
                    vertex[i++] = {{x, y, z + 1, block}, (1 << 1) + 0};
                    vertex[i++] = {{x, y, z + 1, block}, (1 << 1) + 0};
                    vertex[i++] = {{x, y + 1, z, block}, (1 << 1) + 0};
                    vertex[i++] = {{x, y + 1, z + 1, block}, (1 << 1) + 0};
                }
                if (x + 1 == CHUNK_SIZE || GetBlock(x + 1, y, z) == Block::Air) {
                    vertex[i++] = {{x + 1, y, z, block}, (1 << 1) + 1};
                    vertex[i++] = {{x + 1, y, z + 1, block}, (1 << 1) + 1};
                    vertex[i++] = {{x + 1, y + 1, z, block}, (1 << 1) + 1};
                    vertex[i++] = {{x + 1, y + 1, z, block}, (1 << 1) + 1};
                    vertex[i++] = {{x + 1, y, z + 1, block}, (1 << 1) + 1};
                    vertex[i++] = {{x + 1, y + 1, z + 1, block}, (1 << 1) + 1};
                }
                if (y == 0 || GetBlock(x, y - 1, z) == Block::Air) {
                    vertex[i++] = {{x, y, z, block}, (1 << 2) + 0};
                    vertex[i++] = {{x, y, z + 1, block}, (1 << 2) + 0};
                    vertex[i++] = {{x + 1, y, z, block}, (1 << 2) + 0};
                    vertex[i++] = {{x + 1, y, z, block}, (1 << 2) + 0};
                    vertex[i++] = {{x, y, z + 1, block}, (1 << 2) + 0};
                    vertex[i++] = {{x + 1, y, z + 1, block}, (1 << 2) + 0};
                }
                if (y + 1 == MAX_HEIGHT || GetBlock(x, y + 1, z) == Block::Air) {
                    vertex[i++] = {{x, y + 1, z, block}, (1 << 2) + 1};
                    vertex[i++] = {{x + 1, y + 1, z, block}, (1 << 2) + 1};
                    vertex[i++] = {{x, y + 1, z + 1, block}, (1 << 2) + 1};
                    vertex[i++] = {{x + 1, y + 1, z, block}, (1 << 2) + 1};
                    vertex[i++] = {{x + 1, y + 1, z + 1, block}, (1 << 2) + 1};
                    vertex[i++] = {{x, y + 1, z + 1, block}, (1 << 2) + 1};
                }
                if (z == 0 || GetBlock(x, y, z - 1) == Block::Air) {
                    vertex[i++] = {{x, y, z, block}, (1 << 3) + 0};
                    vertex[i++] = {{x + 1, y, z, block}, (1 << 3) + 0};
                    vertex[i++] = {{x, y + 1, z, block}, (1 << 3) + 0};
                    vertex[i++] = {{x + 1, y, z, block}, (1 << 3) + 0};
                    vertex[i++] = {{x + 1, y + 1, z, block}, (1 << 3) + 0};
                    vertex[i++] = {{x, y + 1, z, block}, (1 << 3) + 0};
                }
                if (z + 1 == CHUNK_SIZE || GetBlock(x, y, z + 1) == Block::Air) {
                    vertex[i++] = {{x, y, z + 1, block}, (1 << 3) + 1};
                    vertex[i++] = {{x, y + 1, z + 1, block}, (1 << 3) + 1};
                    vertex[i++] = {{x + 1, y, z + 1, block}, (1 << 3) + 1};
                    vertex[i++] = {{x + 1, y, z + 1, block}, (1 << 3) + 1};
                    vertex[i++] = {{x, y + 1, z + 1, block}, (1 << 3) + 1};
                    vertex[i++] = {{x + 1, y + 1, z + 1, block}, (1 << 3) + 1};
                }
            }
        }
    }
    elements = i;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, elements * (int)sizeof(ChunkVertex), vertex, GL_STATIC_DRAW);
}

void Chunk::Render() {
    if (elements == 0) {
        return;
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, elements);
}

void Chunk::Dump(std::ofstream& file) {
    // binary
    file.write((char*)blocks, sizeof(blocks));
}
void Chunk::Load(std::ifstream& file) {
    // binary
    file.read((char*)blocks, sizeof(blocks));
    needs_update = true;
}
