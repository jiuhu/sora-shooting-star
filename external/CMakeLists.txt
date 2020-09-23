# zlib
wp_add_library(TARGET zlib
  IS_EXTERNAL
  ROOT ${EXTERNAL_DIR}/zlib
  SOURCES adler32.c
          compress.c
          crc32.c
          deflate.c
          gzclose.c
          gzlib.c
          gzread.c
          gzwrite.c
          inflate.c
          infback.c
          inftrees.c
          inffast.c
          trees.c
          uncompr.c
          zutil.c
  )

# lipng
wp_add_library(TARGET libpng
  IS_EXTERNAL
  ROOT ${EXTERNAL_DIR}/libpng
  SOURCES png.c
          pngerror.c
          pngget.c
          pngmem.c
          pngpread.c
          pngread.c
          pngrio.c
          pngrtran.c
          pngrutil.c
          pngset.c
          pngtrans.c
          pngwio.c
          pngwrite.c
          pngwtran.c
          pngwutil.c
  LIBS zlib
  )

# glad
wp_add_library(TARGET glad
  IS_EXTERNAL
  ROOT ${EXTERNAL_DIR}/glad
  SOURCES glad.c
)
