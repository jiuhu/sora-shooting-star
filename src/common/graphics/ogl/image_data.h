#ifndef _WATERPINE_COMMON_GRAPHICS_OGL_IMAGE_DATA_H
#define _WATERPINE_COMMON_GRAPHICS_OGL_IMAGE_DATA_H

#include <string_view>

namespace waterpine {
class ImageData {
 public:
  ImageData(std::string_view fileName);
  ~ImageData();

  bool IsValidData() const { return data_ != nullptr; }
  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }
  unsigned int GetColorFormat() const { return color_format_; }
  const void *GetData() const { return data_; }

 private:
  void LoadPNGFromFile(std::string_view file_name);

  unsigned int width_ = 0;
  unsigned int height_ = 0;
  unsigned int color_format_ = 0;
  unsigned char *data_ = nullptr;
};

}  // namespace waterpine

#endif  // _WATERPINE_COMMON_GRAPHICS_OGL_IMAGE_DATA_H
