
#include "World.h"
#include "Block.h"
#include "Camera.h"

constexpr static int ilog2(int n) {
    int r = 0;
    while (n >>= 1)
        r++;
    return r;
}

constexpr static int LOG_CHUNK_SIZE = ilog2(Chunk::CHUNK_SIZE);

World::World() {
    for (auto& chunkRow : chunks) {
        for (auto& chunk : chunkRow) {
            chunk = std::make_unique<Chunk>();
        }
    }
}

void World::Update() {
    for (auto& chunkRow : chunks) {
        for (auto& chunk : chunkRow) {
            if (chunk != nullptr) {
                chunk->Update();
            }
        }
    }
}

void World::Render(const Camera* camera) {
    shader->Bind();

    shader->setMat4("projection", camera->Projection);
    shader->setMat4("view", camera->View);

    for (int i = 0; i < (int)std::size(chunks); i++) {
        for (int j = 0; j < (int)std::size(chunks[i]); j++) {
            if (chunks[i][j] != nullptr) {
                glm::mat4 model = glm::translate(
                    glm::mat4(1.0f), glm::vec3(i << LOG_CHUNK_SIZE, 0, j << LOG_CHUNK_SIZE));
                shader->setMat4("model", model);
                chunks[i][j]->Render();
            }
        }
    }
}

uint8_t World::GetBlock(int x, int y, int z) const {
    static_assert((Chunk::CHUNK_SIZE & (Chunk::CHUNK_SIZE - 1)) == 0,
                  "Chunk size must be a power of 2");

    int cx = x & (Chunk::CHUNK_SIZE - 1);
    int cz = z & (Chunk::CHUNK_SIZE - 1);

    int chunk_x = x >> LOG_CHUNK_SIZE;
    int chunk_z = z >> LOG_CHUNK_SIZE;

    if (chunk_x < 0 || chunk_x >= (int)std::size(chunks) || chunk_z < 0 ||
        chunk_z >= (int)std::size(chunks[0])) {
        return Block::Air;
    }

    return chunks[chunk_x][chunk_z]->GetBlock(cx, y, cz);
}

void World::SetBlock(int x, int y, int z, uint8_t block) {
    static_assert((Chunk::CHUNK_SIZE & (Chunk::CHUNK_SIZE - 1)) == 0,
                  "Chunk size must be a power of 2");
    int cx = x & (Chunk::CHUNK_SIZE - 1);
    int cz = z & (Chunk::CHUNK_SIZE - 1);
    chunks[x >> LOG_CHUNK_SIZE][z >> LOG_CHUNK_SIZE]->SetBlock(cx, y, cz, block);
}