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
        Dirt = 3,
        Wood = 5,
        Brick = 8,
        Glass = 50,
        JackOLantern = 121,
        NUM_BLOCKS,
    };
    struct Data {
        uint8_t textureFront;
        uint8_t textureBack;
        uint8_t textureLeft;
        uint8_t textureRight;
        uint8_t textureTop;
        uint8_t textureBottom;
        bool islightSource;
        bool isTransparent;

    };

    static inline Data data[257]{};
    static inline std::map<std::string_view, uint8_t> nameLookup{
        {"Air", Block::Air},     {"Grass", Block::Grass}, {"Wood", Block::Wood},
        {"Brick", Block::Brick}, {"Glass", Block::Glass}, {"JackOLantern", Block::JackOLantern}};

    static void Init(const ShaderProgram& program, std::string_view textureFile);
    static void InitBlocks();
    static void AddBlock(uint8_t id, std::string_view name, const Block::Data& data);
};

#endif // OGL_BLOCK_H