#include "gl_vertex_attribute.h"

#include "graphics/gfx.h"

namespace waterpine {

GLVertexAttribute::GLVertexAttribute(unsigned int index, int size, int stride, void *offset)
    : index_(index), size_(size), stride_(stride), offset_(offset) {}

void GLVertexAttribute::Apply() {
  glEnableVertexAttribArray(index_);
  glVertexAttribPointer(index_, size_, GL_FLOAT, GL_FALSE, stride_, offset_);
}

void GLVertexAttribute::Dismiss() {
  glDisableVertexAttribArray(index_);
}

}  // namespace waterpine