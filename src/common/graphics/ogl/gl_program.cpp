#include "gl_program.h"

#include "gl_shader.h"
#include "graphics/gfx.h"
#include "utils/log.h"

namespace waterpine {

GLProgram::GLProgram(const GLShader &vertex_shader, const GLShader &fragment_shader) {
  CreateProgram();
  AttachShader(vertex_shader);
  AttachShader(fragment_shader);
  LinkProgram();
}

GLProgram::~GLProgram() {
  if (IsValid()) {
    glDeleteProgram(program_);
  }
}

void GLProgram::Apply() const {
  glUseProgram(program_);
}

void GLProgram::Dismiss() const {
  glUseProgram(0);
}

int GLProgram::GetAttribLocation(const char *const attrib_name) const {
  return IsValid() ? glGetAttribLocation(program_, attrib_name) : -1;
}

int GLProgram::GetUniformLocation(const char *const uniform_name) const {
  return IsValid() ? glGetUniformLocation(program_, uniform_name) : -1;
}

void GLProgram::SetUniformMatrix(const char *const uniform_name, const float *matrix) const {
  if (auto loc = GetUniformLocation(uniform_name); loc > -1) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
  }
}

bool GLProgram::IsValid() const {
  return glIsProgram(program_);
}

void GLProgram::CreateProgram() {
  program_ = glCreateProgram();
}

void GLProgram::AttachShader(const GLShader &shader) {
  if (!IsValid()) {
    CreateProgram();
  }
  if (shader.IsValid()) {
    glAttachShader(program_, shader.GetShader());
  }
}

void GLProgram::LinkProgram() {
  if (IsValid()) {
    glLinkProgram(program_);

    GLint link_status = GL_FALSE;
    glGetProgramiv(program_, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
      GLint info_length = 0;
      glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &info_length);
      if (info_length) {
        if (char *info_buffer = new char[info_length]; info_buffer) {
          glGetProgramInfoLog(program_, info_length, nullptr, info_buffer);
          LOG_ERROR("Could not link program %d:\n%s\n", program_, info_buffer);
          delete[] info_buffer;
        }
      }
      glDeleteProgram(program_);
    }
  } else {
    LOG_ERROR("Could not create program.\n");
  }
}

}  // namespace waterpine
