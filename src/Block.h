

#ifndef OGL_BLOCK_H
#define OGL_BLOCK_H

#include <array>
#include <string_view>

struct ShaderProgram;


namespace Block {
    enum Block : uint8_t {
        Air = 0,
        Grass = 1,
        Stone = 2,
        NUM_BLOCKS,
    };

    static std::array<Block, Block::NUM_BLOCKS> top_texture = {
        Block::Air,
        Block::Grass,
        Block::Stone,
    };

    void Init(const ShaderProgram& program, std::string_view textureFile);
}



#endif //OGL_BLOCK_H
