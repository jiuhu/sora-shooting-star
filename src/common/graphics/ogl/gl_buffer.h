#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_GL_BUFFER_H_
#define _WATERPINE_COMMON_GRAPHICS_OGL_GL_BUFFER_H_

namespace waterpine {

class GLBuffer {
 public:
  GLBuffer() = default;
  GLBuffer(const float *vertices, unsigned int vertex_count, unsigned int vertex_size);
  ~GLBuffer();

  void CreateVBO(const float *vertices, unsigned int vertex_count, unsigned int vertex_size);
  void CreateIBO(const unsigned short *indices, unsigned int index_count);

  void Apply();
  void Dismiss();

 private:
  unsigned int buffer_{0};
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_GL_BUFFER_H_
