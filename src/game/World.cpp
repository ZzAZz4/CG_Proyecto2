
#include "World.h"
#include "Block.h"
#include "Camera.h"
#include "Time.h"
#include "../rendering/GLWindow.h"
#include <glm/gtc/noise.hpp>
#include <fstream>

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
    time += Time::deltaTime;
    if (time > 24000) {
        time -= 24000;
    }
    for (auto& chunkRow : chunks) {
        for (auto& chunk : chunkRow) {
            if (chunk != nullptr) {
                chunk->Update();
            }
        }
    }
}

void World::Render(const Camera* camera) {
    constexpr static auto mid_color = (day_color + night_color) / 2.0f;
    constexpr static auto color_diff = (day_color - night_color) / 2.0f;
    constexpr static auto factor = 2.0f / 24000.0f * glm::pi<float>();
    shader->Bind();

    shader->setMat4("projection", camera->Projection);
    shader->setMat4("view", camera->View);
    shader->setFloat("ambientIllumination", 0.6f + 0.4f * glm::sin(time * factor));
    GLWindow::active_window->clearColor = mid_color + color_diff * glm::sin(time * factor);

    int i = 0;
    for (const auto& lightSource : lightSources) {
        shader->setVec3("lightSources[" + std::to_string(i) + "]", lightSource + glm::vec3(0.5f));
        i++;
    }
    shader->setInt("lightSourcesCount", i);


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

    if (Block::data[block].islightSource) {
        lightSources.emplace(x, y, z);
    } else if (lightSources.contains(glm::vec3(x, y, z))) {
        lightSources.erase(glm::vec3(x, y, z));
    }
}

static float generate_height_at(int x, int z, int start_layer, int end_layer) {
    float height = 0;
    for (int y = start_layer; y >= end_layer; y--) {
        float divisor = 1 << (y - 1);
        float h = glm::simplex(glm::vec2((float)x / divisor, (float)z / divisor));
        height += h;
    }
    return height / (float)(start_layer - end_layer + 1);
}

static uint8_t BlockAt(int x, int y, int z, int desiredHeight) {
    if (y < 25 && y > desiredHeight) {
        return Block::Water;
    } else if (y == desiredHeight) {
        return Block::Grass;
    } else if (y < desiredHeight) {
        return Block::Dirt;
    } else {
        return Block::Air;
    }
}


void World::Randomize() {
    for (int x = 0; x < DIAMETER_X; x++) {
        for (int z = 0; z < DIAMETER_Z; z++) {
            float height = generate_height_at(x, z, 8, 5);
            height = (height + 1) / 2;
            height *= 56.0f;
            int y_max = (int)height + 1;
            for (int y = 0; y <= glm::max(y_max, 25); y++) {
                SetBlock(x, y, z, BlockAt(x, y, z, y_max));
            }
        }
    }
}

int World::GetHeightAt(int x, int z) const {
    for (int y = 255; y >= 0; y--) {
        if (GetBlock(x, y, z) != Block::Air) {
            return y;
        }
    }
    return 0;
}
void World::Dump(std::ofstream& ofstream) {
    // binary
    ofstream.write((char*)&time, sizeof(time));
    std::size_t lightSourcesSize = lightSources.size();
    ofstream.write((char*)&lightSourcesSize, sizeof(lightSourcesSize));
    for (const glm::vec3& lightSource : lightSources) {
        ofstream.write((char*)&lightSource, sizeof(lightSource));
    }
    for (int i = 0; i < (int)std::size(chunks); i++) {
        for (int j = 0; j < (int)std::size(chunks[i]); j++) {
            if (chunks[i][j] != nullptr) {
                ofstream.write((char*)&i, sizeof(i));
                ofstream.write((char*)&j, sizeof(j));
                chunks[i][j]->Dump(ofstream);
            }
        }
    }
    int end = -1;
    ofstream.write((char*)&end, sizeof(end));
    ofstream.write((char*)&end, sizeof(end));
}

void World::Load(std::ifstream& ifstream) {
    // binary
    ifstream.read((char*)&time, sizeof(time));
    std::size_t lightSourcesSize;
    ifstream.read((char*)&lightSourcesSize, sizeof(lightSourcesSize));
    for (std::size_t i = 0; i < lightSourcesSize; i++) {
        glm::vec3 lightSource;
        ifstream.read((char*)&lightSource, sizeof(lightSource));
        lightSources.emplace(lightSource);
    }
    while (true) {
        int i, j;
        ifstream.read((char*)&i, sizeof(i));
        if (i == -1) {
            break;
        }
        ifstream.read((char*)&j, sizeof(j));
        chunks[i][j] = std::make_unique<Chunk>();
        chunks[i][j]->Load(ifstream);
    }
    Update();
}
