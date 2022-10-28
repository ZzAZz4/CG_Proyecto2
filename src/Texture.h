

#ifndef OGL_TEXTURE_H
#define OGL_TEXTURE_H

#include "types.h"
#include <string_view>

struct Texture2D {
    unsigned int id;

    Texture2D(const u8* data, int width, int height, int channels);
    static Texture2D FromFile(std::string_view path);
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&& o) noexcept;
    Texture2D& operator=(Texture2D&& o) noexcept;
    ~Texture2D();



    void Bind() const;
    void Bind(unsigned int slot) const;
    static void UnbindAny();
    static void UnbindAny(unsigned int slot);

    bool isValid() const;
};


#endif //OGL_TEXTURE_H
