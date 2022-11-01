
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <fstream>
#include "Shader.h"

Shader::Shader (int type, std::string_view sourceCode) {
    id = glCreateShader(type);
    const char* sourceCodePtr = sourceCode.data();
    glShaderSource(id, 1, &sourceCodePtr, nullptr);
    glCompileShader(id);

    // Check for errors
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile shader: " + std::string(infoLog));
    }
}

Shader Shader::FromFile (int type, std::string_view path) {
    std::ifstream file(path.data());
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(path));
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return {type, content};
}

Shader::~Shader () {
    glDeleteShader(id);
}
