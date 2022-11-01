#ifndef OGL_BLOCK_H
#define OGL_BLOCK_H

#include <array>
#include <string_view>
#include <unordered_map>
#include <memory>

struct ShaderProgram;

namespace Block {
    enum Block : uint8_t {
        Air = 0,
        Grass = 1,
        Stone = 2,
        Wood = 5,
        Brick = 8,
        Glass = 50,
        NUM_BLOCKS,
    };

    void Init(const ShaderProgram& program, std::string_view textureFile);

}

static std::unordered_map<std::string, uint8_t> blockMap {
    {"Air", Block::Air},
    {"Grass", Block::Grass},
    {"Wood", Block::Wood},
    {"Brick", Block::Brick},
    {"Glass", Block::Glass}
};

#endif //OGL_BLOCK_H