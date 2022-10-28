
#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>
#include "Texture.h"

static i32 find_format(i32 channels) {
    switch (channels) {
        case 1: return GL_RED;
        case 2: return GL_RG;
        case 3: return GL_RGB;
        case 4: return GL_RGBA;
        default: return 0;
    }
}

Texture2D::Texture2D (const u8* data, int width, int height, int channels) {
    glGenTextures(1, &id);

    i32 format = find_format(channels);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
        format == GL_RGBA ? GL_CLAMP_TO_EDGE
                          : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

Texture2D::~Texture2D () {
    glDeleteTextures(1, &id);
}

void Texture2D::Bind () const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::Bind (unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::UnbindAny () {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::UnbindAny (unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture2D::Texture2D (Texture2D&& o) noexcept {
    this->id = o.id;
    o.id = 0;
}
Texture2D& Texture2D::operator = (Texture2D&& o) noexcept {
    this->id = o.id;
    o.id = 0;
    return *this;
}

Texture2D Texture2D::FromFile (std::string_view path) {
    int width, height, nrComponents;
    u8* data = stbi_load(path.data(), &width, &height, &nrComponents, 0);

    if (!data) {
        throw std::runtime_error("Failed to load texture " + std::string(path));
    }
    Texture2D tex{ data, width, height, nrComponents };
    stbi_image_free(data);
    return tex;
}
