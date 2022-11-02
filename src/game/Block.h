#ifndef OGL_BLOCK_H
#define OGL_BLOCK_H

#include <array>
#include <map>
#include <memory>
#include <string_view>

struct ShaderProgram;

struct Block {
    enum Type : uint8_t {
        Air = 0,
        Grass = 1,
        Stone = 2,
        Wood = 5,
        Brick = 8,
        Glass = 50,
        JackOLantern = 121,
        NUM_BLOCKS,
    };

    static inline bool isLightSource[NUM_BLOCKS] = {false};
    static void Init(const ShaderProgram& program, std::string_view textureFile);

};

static std::map<std::string, uint8_t> blockMap{{"Air", Block::Air},
                                               {"Grass", Block::Grass},
                                               {"Wood", Block::Wood},
                                               {"Brick", Block::Brick},
                                               {"Glass", Block::Glass},
                                               {"JackOLantern", Block::JackOLantern}};

#endif // OGL_BLOCK_H