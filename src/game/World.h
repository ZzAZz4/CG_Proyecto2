

#ifndef OGL_WORLD_H
#define OGL_WORLD_H

#include "../rendering/ShaderProgram.h"
#include "Camera.h"
#include "Chunk.h"
#include <memory>

struct World {
    constexpr static int CHUNKS_IN_X = 16;
    constexpr static int CHUNKS_IN_Z = 16;
    constexpr static int DIAMETER_X = CHUNKS_IN_X * Chunk::CHUNK_SIZE;
    constexpr static int DIAMETER_Z = CHUNKS_IN_Z * Chunk::CHUNK_SIZE;

    constexpr static const auto day_color = glm::vec4{0.4f, 0.6f, 0.9f, 1.0f};
    constexpr static const auto night_color = glm::vec4{0.08f, 0.08f, 0.2f, 1.0f};

    std::unique_ptr<Chunk> chunks[CHUNKS_IN_X][CHUNKS_IN_Z];
    std::unique_ptr<ShaderProgram> shader;
    float time = 0;

    World();
    void Randomize();

    uint8_t GetBlock(int x, int y, int z) const;
    void SetBlock(int x, int y, int z, uint8_t block);
    int GetHeightAt(int x, int z) const;
    void Update();
    void Render(const Camera* camera);
};

#endif // OGL_WORLD_H
