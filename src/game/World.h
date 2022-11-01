

#ifndef OGL_WORLD_H
#define OGL_WORLD_H

#include "Chunk.h"
#include "../rendering/ShaderProgram.h"
#include "Camera.h"
#include <memory>

struct World {
    std::unique_ptr<Chunk> chunks[2][2];
    std::unique_ptr<ShaderProgram> shader;

    World();

    uint8_t GetBlock(int x, int y, int z) const;
    void SetBlock(int x, int y, int z, uint8_t block);
    void Update();
    void Render (const Camera* camera);
};


#endif //OGL_WORLD_H
