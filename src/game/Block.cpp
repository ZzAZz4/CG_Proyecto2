
#include "Block.h"
#include "../rendering/ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <stb_image.h>
#include <stdexcept>

static unsigned int textureID[6];

static unsigned char buffer[257][16][16][4];

static void copy_subimage(int image, int width, int channels, const unsigned char* data,
                          int subimage_width, int subimage_height, unsigned char* subimage_data) {
    int i = 0;
    for (int y = 0; y < subimage_height; ++y) {
        for (int x = 0; x < subimage_width; ++x) {
            int pixel_x = (image % 16) * subimage_width + x;
            int pixel_y = (image / 16) * subimage_height + y;
            int pixel_index = (pixel_y * width + pixel_x) * channels;
            for (int c = 0; c < channels; ++c) {
                subimage_data[i++] = data[pixel_index++];
            }
        }
    }
    // flip the image vertically
    for (int y = 0; y < subimage_height / 2; ++y) {
        for (int x = 0; x < subimage_width; ++x) {
            for (int c = 0; c < channels; ++c) {
                int i1 = (y * subimage_width + x) * channels + c;
                int i2 = ((subimage_height - y - 1) * subimage_width + x) * channels + c;
                unsigned char temp = subimage_data[i1];
                subimage_data[i1] = subimage_data[i2];
                subimage_data[i2] = temp;
            }
        }
    }
}

static void load_face(int face, int subimage_width, int subimage_height, const ShaderProgram& shader) {
    auto memberPtr = face == 0 ? &Block::Data::textureBack :
                     face == 1 ? &Block::Data::textureFront :
                     face == 2 ? &Block::Data::textureBottom :
                     face == 3 ? &Block::Data::textureTop :
                     face == 4 ? &Block::Data::textureLeft : &Block::Data::textureRight;

    glActiveTexture(GL_TEXTURE0 + face);
    glGenTextures(1, &textureID[face]);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID[face]);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, subimage_width, subimage_height, 257, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    for (int id = 1; id <= 256; ++id) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, id, subimage_width, subimage_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer[Block::data[id].*memberPtr][0][0]);
    }
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    shader.setInt("tex[" + std::to_string(face) + "]", face);
}

void Block::Init(const ShaderProgram& program, std::string_view textureFile) {
    InitBlocks();

    int width, height, channels;

    unsigned char* data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load block texture");
    }

    const auto subimage_width = width / 16;
    const auto subimage_height = height / 16;

    for (int image = 0; image < 256; ++image) {
        copy_subimage(image, width, channels, data, subimage_width, subimage_height, buffer[image + 1][0][0]);
    }
    stbi_image_free(data);

    program.Bind();

    load_face(0, subimage_width, subimage_height, program);
    load_face(1, subimage_width, subimage_height, program);
    load_face(2, subimage_width, subimage_height, program);
    load_face(3, subimage_width, subimage_height, program);
    load_face(4, subimage_width, subimage_height, program);
    load_face(5, subimage_width, subimage_height, program);
}

void Block::AddBlock(uint8_t id, std::string_view name, const Block::Data& d) {
    nameLookup[name] = id;
    data[id] = d;
}

void Block::InitBlocks() {
    AddBlock(Air, "Air", {0, 0, 0, 0, 0, 0, false, true, 1.0f});
    AddBlock(Grass, "Grass", Data{4, 4, 4, 4, 1, 3, false, false, 0.0f});
    AddBlock(Stone, "Stone", {2, 2, 2, 2, 2, 2, false, false, 0.0f});
    AddBlock(Dirt, "Dirt", {3, 3, 3, 3, 3, 3, false, false, 0.0f});
    AddBlock(Wood, "Wood", {5, 5, 5, 5, 5, 5, false, false, 0.0f});
    AddBlock(Brick, "Brick", {8, 8, 8, 8, 8, 8, false, false, 0.0f});
    AddBlock(Glass, "Glass", {50, 50, 50, 50, 50, 50, false, true, 0.0f});
    AddBlock(JackOLantern, "JackOLantern", Data{121, 119, 119, 119, 103, 103, true, false, 0.0f});
    AddBlock(Water, "Water", Data{207, 207, 207, 207, 207, 207, false, true, 0.5f});
}
