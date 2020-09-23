function(wp_add_library)
  set(options IS_EXTERNAL)
  set(oneValueArgs TARGET ROOT)
  set(multiValueArgs SOURCES LIBS)
  cmake_parse_arguments(OPTIONS
      "${options}"
      "${oneValueArgs}"
      "${multiValueArgs}"
      ${ARGN}
      )

  if(NOT OPTIONS_TARGET)
    message(FATAL_ERROR "Missing required TARGET argument in wp_add_library")
  endif()

  project(${OPTIONS_TARGET})

  message("Adding library: ${OPTIONS_TARGET}")

  if(OPTIONS_ROOT)
    foreach(src ${OPTIONS_SOURCES})
      list(APPEND SOURCES ${OPTIONS_ROOT}/${src})
    endforeach()
  else()
    list(APPEND SOURCES ${OPTIONS_SOURCES})
  endif()

  add_library(${OPTIONS_TARGET} ${SOURCES})

  if(OPTIONS_LIBS)
    foreach(lib ${OPTIONS_LIBS})
      list(APPEND LIB_DIRS ${EXTERNAL_DIR}/${lib})
    endforeach()

    list(APPEND LIBS ${OPTIONS_LIBS})
    target_link_libraries(${OPTIONS_TARGET} ${LIBS})
  endif()

  target_include_directories(${OPTIONS_TARGET} PUBLIC
      ${EXTERNAL_DIR}
      ${LIB_DIRS}
      ${OPTIONS_ROOT}
      )

  if (OPTIONS_IS_EXTERNAL)
    set(TYPE external)
  else()
    set(TYPE waterpine)
  endif()

  set_target_properties(${OPTIONS_TARGET}
      PROPERTIES FOLDER ${TYPE}
      )
endfunction()
