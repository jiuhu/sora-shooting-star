#ifndef _COMMON_OGL_GFX_H
#define _COMMON_OGL_GFX_H

#include "os/platform.h"

#ifdef __OPENGL__

#include <glad/glad.h>

#elif __GLES__
#include <GLES3/gl3.h>
#endif

#endif  // _COMMON_OGL_GFX_H
