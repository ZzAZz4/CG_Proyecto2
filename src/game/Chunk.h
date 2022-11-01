

#ifndef OGL_CHUNK_H
#define OGL_CHUNK_H

#include "../math/types.h"

struct Chunk {
    constexpr static int CHUNK_SIZE = 32;
    constexpr static int MAX_HEIGHT = 256;

    std::uint8_t blocks[CHUNK_SIZE][MAX_HEIGHT][CHUNK_SIZE];
    unsigned int VAO;
    unsigned int VBO;
    int elements;
    bool needs_update;

    Chunk();
    ~Chunk();

    uint8_t GetBlock(int x, int y, int z) const;
    void SetBlock(int x, int y, int z, uint8_t block);
    void Update();
    void Render();
};


#endif //OGL_CHUNK_H
