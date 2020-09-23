#include "gl_buffer.h"

#include "graphics/gfx.h"

namespace waterpine {

GLBuffer::GLBuffer(const float *vertices, unsigned int vertex_count, unsigned int vertex_size) {
  CreateVBO(vertices, vertex_count, vertex_size);
}

GLBuffer::~GLBuffer() {
  if (glIsBuffer(buffer_)) {
    glDeleteBuffers(1, &buffer_);
  }
}

void GLBuffer::CreateVBO(const float *vertices, unsigned int vertex_count, unsigned int vertex_size) {
  glGenBuffers(1, &buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_);
  glBufferData(
      GL_ARRAY_BUFFER, vertex_count * vertex_size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void GLBuffer::CreateIBO(const unsigned short *indices, unsigned int index_count) {
  glGenBuffers(1, &buffer_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

void GLBuffer::Apply() {
  glBindBuffer(GL_ARRAY_BUFFER, buffer_);
}

void GLBuffer::Dismiss() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}  // namespace waterpine
