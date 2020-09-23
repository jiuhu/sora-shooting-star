wp_add_library(TARGET common
  ROOT ${CMAKE_SOURCE_DIR}/src/common

  SOURCES
    graphics/ogl/gl_buffer.h
    graphics/ogl/gl_buffer.cpp
    graphics/ogl/gl_program.h
    graphics/ogl/gl_program.cpp
    graphics/ogl/gl_shader.h
    graphics/ogl/gl_shader.cpp
    graphics/ogl/gl_texture.h
    graphics/ogl/gl_texture.cpp
    graphics/ogl/gl_vertex_array.h
    graphics/ogl/gl_vertex_array.cpp
    graphics/ogl/gl_vertex_attribute.h
    graphics/ogl/gl_vertex_attribute.cpp
    graphics/ogl/image_data.h
    graphics/ogl/image_data.cpp
    graphics/gfx.h
    graphics/gfx_object.h
    os/os_utils.h
    os/${WP_PLATFORM}/os_utils.cpp
    utils/log.h
  )