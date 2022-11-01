
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../rendering/ShaderProgram.h"
#include <stb_image.h>
#include <stdexcept>
#include "Block.h"
#include <memory>

static unsigned int textureID = 0;

static void copy_subimage (int image, int width, int channels, const unsigned char* data,
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
}


void Block::Init (const ShaderProgram& program, std::string_view textureFile) {
    int width, height, channels;
    unsigned char* data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load block texture");
    }

    glActiveTexture(GL_TEXTURE0);

    const auto subimage_width = width / 16;
    const auto subimage_height = height / 16;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, subimage_width, subimage_height, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    auto subimage_data = std::make_unique<unsigned char[]>(subimage_width * subimage_height * channels);
    for (int image = 0; image < 256; ++image) {
        copy_subimage(image, width, channels, data, subimage_width, subimage_height, subimage_data.get());
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, image, subimage_width, subimage_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, subimage_data.get());
    }
    stbi_image_free(data);

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    program.Bind();
    program.setInt("tex", 0);

}
