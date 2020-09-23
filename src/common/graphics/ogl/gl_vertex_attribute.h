#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ATTRIBUTE_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ATTRIBUTE_H_

namespace waterpine {

class GLVertexAttribute {
 public:
  GLVertexAttribute(unsigned int index, int size, int stride, void *offset);
  ~GLVertexAttribute() = default;

  void Apply();
  void Dismiss();

 private:
  unsigned int index_;
  int size_;
  int stride_;
  void *offset_;
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ATTRIBUTE_H_
