
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include <stb_image.h>
#include <stdexcept>
#include "Block.h"

static unsigned int textureID = 0;

void Block::Init (const ShaderProgram& program, std::string_view textureFile) {
    int width, height, channels;
    unsigned char* data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load block texture");
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    program.Bind();
    program.setInt("tex", 0);
}
