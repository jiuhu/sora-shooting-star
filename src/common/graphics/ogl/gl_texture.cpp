#include "gl_texture.h"

#include "graphics/gfx.h"
#include "image_data.h"

namespace waterpine {

GLTexture::GLTexture(std::string_view file_name) {
  LoadTexture(file_name);
}

GLTexture::~GLTexture() {
  if (texture_id_) {
    glDeleteTextures(1, &texture_id_);
  }
}

bool GLTexture::LoadTexture(std::string_view file_name) {
  glGenTextures(1, &texture_id_);
  if (const ImageData image(file_name); image.IsValidData()) {
    BindTexture(image.GetWidth(), image.GetHeight(), image.GetColorFormat(), image.GetData());
    printf("Loaded texture %s to id %d\n", file_name, texture_id_);
  } else {
    printf("Loaded invalid texture %s\n", file_name);
    glDeleteTextures(1, &texture_id_);
    return false;
  }

  return true;
}

void GLTexture::BindTexture(const int width,
                            const int height,
                            const unsigned int type,
                            const void *pixels) {
  glBindTexture(GL_TEXTURE_2D, texture_id_);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
}

void GLTexture::Apply() {
  glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void GLTexture::Dismiss() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace waterpine
