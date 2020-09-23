#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_PROGRAM_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_PROGRAM_H_

namespace waterpine {

class GLShader;

class GLProgram {
 public:
  GLProgram() = default;
  GLProgram(const GLShader &vertex_shader, const GLShader &fragment_shader);

  ~GLProgram();

  void AttachShader(const GLShader &shader);
  void LinkProgram();
  bool IsValid() const;

  void Apply() const;
  void Dismiss() const;

  int GetAttribLocation(const char *const attrib_name) const;
  int GetUniformLocation(const char *const uniform_name) const;

  void SetUniformMatrix(const char *const uniform_name, const float *matrix) const;

 private:
  void CreateProgram();

  unsigned int program_{0};
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_PROGRAM_H_
