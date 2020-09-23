#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_TEXTURE_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_TEXTURE_H_

#include <string>

namespace waterpine {

class GLTexture {
 public:
  GLTexture() = default;
  GLTexture(std::string_view file_name);
  ~GLTexture();

  bool LoadTexture(std::string_view file_name);
  void BindTexture(const int width, const int height, const unsigned int type, const void *pixels);

  void Apply();
  void Dismiss();

 private:
  unsigned int texture_id_{0};
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_TEXTURE_H_
