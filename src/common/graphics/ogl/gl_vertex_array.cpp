#include "gl_vertex_array.h"

#include "graphics/gfx.h"

namespace waterpine {

GLVertexArray::GLVertexArray() {
  vertex_attributes_.reserve(4);
}

void GLVertexArray::AddVertexAttribute(GLVertexAttribute &&attribute) {
  vertex_attributes_.emplace_back(std::move(attribute));
}

void GLVertexArray::SetBuffer(const float *vertices, unsigned int vertex_count, unsigned int vertex_size) {
  buffer_.CreateVBO(vertices, vertex_count, vertex_size);
}

void GLVertexArray::Apply() {
  buffer_.Apply();
  for (auto &attrib : vertex_attributes_) {
    attrib.Apply();
  }
}

void GLVertexArray::Dismiss() {
  for (auto &attrib : vertex_attributes_) {
    attrib.Dismiss();
  }
  buffer_.Dismiss();
}

void GLVertexArray::Draw(int mode, int count) {
  Apply();
  glDrawArrays(mode, 0, count);
//  Dismiss();
}

}  // namespace waterpine