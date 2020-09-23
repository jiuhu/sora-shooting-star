#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ARRAY_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ARRAY_H_

#include <vector>

#include "gl_buffer.h"
#include "gl_vertex_attribute.h"

namespace waterpine {

class GLVertexArray {
 public:
  GLVertexArray() = default;
  ~GLVertexArray() = default;

  void AddVertexAttribute(GLVertexAttribute &&attribute);
  void SetBuffer(const float *vertices, unsigned int vertex_count, unsigned int vertex_size);

  void Apply();
  void Dismiss();

  void Draw(int mode, int count);

 private:
  GLBuffer buffer_;
  std::vector<GLVertexAttribute> vertex_attributes_;
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_VERTEX_ARRAY_H_
