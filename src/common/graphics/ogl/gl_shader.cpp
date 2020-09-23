#include "gl_shader.h"

#include "graphics/gfx.h"
#include "utils/log.h"

namespace waterpine {

GLShader::GLShader(ShaderType shader_type, const char *const shader_code) {
  shader_ = glCreateShader(shader_type == ShaderType::VERTEX_SHADER ? GL_VERTEX_SHADER
                                                                    : GL_FRAGMENT_SHADER);
  if (IsValid()) {
    glShaderSource(shader_, 1, &shader_code, nullptr);
    glCompileShader(shader_);

    GLint compile_status = GL_FALSE;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
      GLint info_length = 0;
      glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &info_length);
      if (info_length) {
        if (char *info_buffer = new char[info_length]; info_buffer) {
          glGetShaderInfoLog(shader_, info_length, nullptr, info_buffer);
          LOG_ERROR("Could not compile shader %d:\n%s\n", shader_, info_buffer);
          delete[] info_buffer;
        }
        glDeleteShader(shader_);
      }
    }
  }
}

GLShader::~GLShader() {
  if (IsValid()) {
    glDeleteShader(shader_);
  }
}

bool GLShader::IsValid() const {
  return glIsShader(shader_);
}

unsigned int GLShader::GetShader() const {
  return shader_;
}

}  // namespace waterpine
