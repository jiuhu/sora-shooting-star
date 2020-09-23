#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_SHADER_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_SHADER_H_

#include <string_view>

namespace waterpine {

enum class ShaderType {
  VERTEX_SHADER,
  FRAGMENT_SHADER,
};

class GLShader {
 public:
  GLShader(ShaderType shader_type, const char *const shader_code);
  ~GLShader();

  bool IsValid() const;
  unsigned int GetShader() const;

 private:
  unsigned int shader_ = 0;
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_SHADER_H_
