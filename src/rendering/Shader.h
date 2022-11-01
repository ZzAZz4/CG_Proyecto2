

#ifndef OGL_SHADER_H
#define OGL_SHADER_H

#include <string_view>

struct Shader {
    int id;

    Shader(int type, std::string_view sourceCode);
    static Shader FromFile(int type, std::string_view path);

    ~Shader();
    Shader(const Shader&) = delete;
    Shader(Shader&) = delete;
    Shader(Shader&&) noexcept = delete;
    Shader& operator=(Shader&) = delete;
    Shader& operator=(Shader&&) noexcept = delete;
};


#endif //OGL_SHADER_H
