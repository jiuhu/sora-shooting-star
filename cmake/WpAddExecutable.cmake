function(wp_add_executable)
  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES RESOURCES)
  cmake_parse_arguments(OPTIONS
      "${options}"
      "${oneValueArgs}"
      "${multiValueArgs}"
      ${ARGN}
      )

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/${OPTIONS_TARGET})

  if(NOT OPTIONS_TARGET)
    message(FATAL_ERROR "Missing required TARGET argument in wp_add_executable")
  endif()
  project(${OPTIONS_TARGET})

  if(OPTIONS_SOURCES)
    list(APPEND SOURCES ${OPTIONS_SOURCES})
  endif()

  add_executable(${OPTIONS_TARGET} ${SOURCES})

  target_include_directories(${OPTIONS_TARGET} PUBLIC
      ${CMAKE_SOURCE_DIR}/src/common
      ${EXTERNAL_DIR}
      )

  target_link_directories(${OPTIONS_TARGET} PUBLIC
      ${EXTERNAL_DIR}/lib/${WP_PLATFORM}
      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
      )

  list(APPEND COMMON_LIBS
      libpng
      glad
      common
      )

  if(OPTIONS_RESOURCES)
    foreach(rc ${OPTIONS_RESOURCES})
      message("RC:" ${rc})
      list(APPEND RESOURCE_FILES ${ASSETS_DIR}/${rc})
    endforeach()
  endif()

  if(${WP_PLATFORM} STREQUAL "html5")
    set_target_properties(${OPTIONS_TARGET} PROPERTIES
        LINK_FLAGS "--emrun -s USE_GLFW=3 -s FULL_ES3=1 -s USE_WEBGL2=1 --use-preload-plugins --preload-file ${ASSETS_DIR}@/"
        )

    add_custom_command(TARGET ${OPTIONS_TARGET} POST_BUILD
        COMMAND python ${SCRIPTS_DIR}/generate_html.py ${OPTIONS_TARGET} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${OPTIONS_TARGET}.html
        )
  else()
    find_package(OpenGL REQUIRED)
    list(APPEND COMMON_LIBS
        ${OPENGL_LIBRARIES}
        glfw3
        )
    if(MSVC)
      set_target_properties(${OPTIONS_TARGET} PROPERTIES
          VS_DEBUGGER_WORKING_DIRECTORY ${ASSETS_DIR}
          )

      install(TARGETS ${OPTIONS_TARGET}
          RESOURCE DESTINATION ${BIN_DIR}/${OPTIONS_TARGET}
          )
    elseif(APPLE)
#      set(IOS True)
      target_link_libraries(${OPTIONS_TARGET} PUBLIC
          "-framework Cocoa"
          "-framework CoreVideo"
          "-framework IOKit")

      set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")

      set_target_properties(${OPTIONS_TARGET} PROPERTIES
          MACOSX_BUNDLE TRUE
          MACOSX_FRAMEWORK_IDENTIFIER com.${OPTIONS_TARGET}
          RESOURCE "${RESOURCE_FILES}"
          )
    endif()
  endif()

  target_link_libraries(${OPTIONS_TARGET} PUBLIC
      ${COMMON_LIBS}
      )

  set_target_properties(${OPTIONS_TARGET}
      PROPERTIES FOLDER project
      )
endfunction()
