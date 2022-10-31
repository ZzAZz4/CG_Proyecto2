

#ifndef OGL_WORLD_H
#define OGL_WORLD_H

#include "Chunk.h"
#include "ShaderProgram.h"
#include <memory>

struct World {
    std::unique_ptr<Chunk> chunks[2][2];
    ShaderProgram* shader = nullptr;

    World();

    uint8_t GetBlock(int x, int y, int z) const;
    void SetBlock(int x, int y, int z, uint8_t block);
    void Update();
    void Render();
};


#endif //OGL_WORLD_H
