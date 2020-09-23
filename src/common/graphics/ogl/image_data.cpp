#include "image_data.h"

#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#else  // __WIN32__

#include <glad/glad.h>

#endif

#include <libpng/png.h>

namespace waterpine {

GLuint SelectColorType(png_structp &png, int pngColorType) {
  switch (pngColorType) {
      // case PNG_COLOR_TYPE_GRAY:
      //  return GL_LUMINANCE;

      // case PNG_COLOR_TYPE_GRAY_ALPHA:
      //  return GL_LUMINANCE_ALPHA;

    case PNG_COLOR_TYPE_PALETTE:
      png_set_palette_to_rgb(png);
    case PNG_COLOR_TYPE_RGB:
      png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
      // return GL_RGB;

    case PNG_COLOR_TYPE_RGB_ALPHA:
      return GL_RGBA;

    default:
      printf("Unknown PNG color type.\n");
      return 0;
  }
}

ImageData::ImageData(std::string_view fileName) {
  LoadPNGFromFile(fileName);
}

ImageData::~ImageData() {
  if (data_ != nullptr) {
    delete[] data_;
  }
}

void ImageData::LoadPNGFromFile(std::string_view file_name) {
  if (FILE *fp = fopen(file_name.data(), "rb"); fp != 0) {
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (!png_sig_cmp(header, 0, 8)) {
      png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      if (png && !setjmp(png_jmpbuf(png))) {
        png_infop pngInfo = png_create_info_struct(png);
        png_infop pngEndInfo = png_create_info_struct(png);
        if (pngInfo && pngEndInfo) {
          png_init_io(png, fp);
          png_set_sig_bytes(png, 8);
          png_read_info(png, pngInfo);

          int bitDepth, colorType;
          png_get_IHDR(png, pngInfo, &width_, &height_, &bitDepth, &colorType, NULL, NULL, NULL);

          if (png_get_valid(png, pngInfo, PNG_INFO_tRNS)) {
            png_set_tRNS_to_alpha(png);
          }

          if (bitDepth < 8) {
            png_set_packing(png);
          } else if (bitDepth == 16) {
            printf("16 bit image not supported\n");
          }

          color_format_ = SelectColorType(png, colorType);

          png_read_update_info(png, pngInfo);

          png_size_t rowbytes = png_get_rowbytes(png, pngInfo);
          data_ = new unsigned char[rowbytes * height_];
          if (data_) {
            png_bytep *row_pointers = new png_bytep[height_];
            if (row_pointers) {
              for (unsigned int i = 0; i < height_; ++i) row_pointers[i] = data_ + i * rowbytes;
              png_read_image(png, row_pointers);
              delete[] row_pointers;
            }
          }
        }
        png_destroy_read_struct(&png, &pngInfo, &pngEndInfo);
      }
    } else {
      printf("Bad header! Invalid PNG format.\n");
    }

    fclose(fp);
  } else {
    printf("Invalid file detected: %s\n", file_name);
  }
}

}  // namespace waterpine
