#ifndef _COMMON_GRAPHICS_OGL_SHADER_SRC_H
#define _COMMON_GRAPHICS_OGL_SHADER_SRC_H

const char *vs() {
  return "attribute vec4 vPosition;         "
         "uniform mat4 mMVP;                "
         "void main()                       "
         "{                                 "
         "   gl_Position = mMVP * vPosition;"
         "}                                 ";
}

const char *texture_vs() {
  return "attribute vec4 vPosition;        \n"
         "attribute vec2 vTexCoord;         "
         "varying vec2 fTexCoord;           "
         "uniform mat4 mMVP;                "
         "void main()                       "
         "{                                 "
         "   gl_Position = mMVP * vPosition;"
         "   fTexCoord = vTexCoord;         "
         "}                                 ";
}

const char *red_fs() {
  return "void main()                               "
         "{                                         "
         "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
         "}                                         ";
}

const char *texture_fs() {
  return
#ifdef __GLES__
      "precision mediump float;                     \n"
#endif
      "varying vec2 fTexCoord;                        "
      "uniform sampler2D texture;                     "
      "void main()                                    "
      "{                                              "
      "  gl_FragColor = texture2D(texture, fTexCoord);"
      "}                                              ";
}

#endif  // _COMMON_GRAPHICS_OGL_SHADER_SRC_H
