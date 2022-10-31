
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include <stb_image.h>
#include <stdexcept>
#include "Block.h"
#include <memory>

static unsigned int textureID = 0;

void Block::Init (const ShaderProgram& program, std::string_view textureFile) {
    int width, height, channels;
    unsigned char* data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load block texture");
    }

    glActiveTexture(GL_TEXTURE0);

    const auto subimage_width = width / 16;
    const auto subimage_height = height / 16;

    stbi_image_free(data);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, subimage_width, subimage_height, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    std::unique_ptr<unsigned char[]> subimage_data = std::make_unique<unsigned char[]>(subimage_width * subimage_height * channels);
    for (int image = 0; image < 256; ++image) {
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
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, image, subimage_width, subimage_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, subimage_data.get());
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    program.Bind();
    program.setInt("tex", 0);

}
