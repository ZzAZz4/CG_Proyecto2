

#ifndef OGL_BLOCK_H
#define OGL_BLOCK_H

#include <array>
#include <memory>
#include <string_view>

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

} // namespace Block

#endif // OGL_BLOCK_H
