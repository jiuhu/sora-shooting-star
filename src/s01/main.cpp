#include "graphics/ogl/gl_program.h"
#include "graphics/ogl/gl_shader.h"
#include "graphics/ogl/gl_texture.h"
#include "graphics/ogl/shader_src.h"
#include "graphics/ogl/gl_vertex_array.h"
#include "os/os_utils.h"
#include "graphics/gfx.h"

#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "math/mat44.h"
#include "math/vec3.h"

namespace {
  constexpr auto kStride = sizeof(GLfloat) * 4;
  constexpr auto kTexCoordOffset = sizeof(GLfloat) * 2;

  waterpine::GLProgram sprite_shader;

  waterpine::GLTexture player_ship;
  waterpine::GLTexture enemy_turret;
  waterpine::GLVertexArray quad_;
waterpine::GLVertexArray quad_big_;

  wpmath::Vec3 position{320.0f, 400.0f, 0.0f};
  wpmath::Vec3 turret_position{320.0f, 50.0f, 0.0f};
  float MoveStep = 8.0f;

  const wpmath::Mat44 kProjection = wpmath::OrthoProjection(640.0f, 480.0f);
}

void Init() {
  waterpine::GLShader vs(waterpine::ShaderType::VERTEX_SHADER, texture_vs());
  waterpine::GLShader fs(waterpine::ShaderType::FRAGMENT_SHADER, texture_fs());

  sprite_shader.AttachShader(vs);
  sprite_shader.AttachShader(fs);
  sprite_shader.LinkProgram();

  auto vp = sprite_shader.GetAttribLocation("vPosition");
  auto vt = sprite_shader.GetAttribLocation("vTexCoord");

  {
    const GLfloat vertices[] = {
        -16.0f, -16.0f, 0.0f, 0.0f,
        -16.0f, 16.0f, 0.0f, 1.0f,
        16.0f, -16.0f, 1.0f, 0.0f,
        16.0f, 16.0f, 1.0f, 1.0f,
    };
    quad_.SetBuffer(vertices, 4, 4);
    quad_.AddVertexAttribute(waterpine::GLVertexAttribute(vp, 2, kStride, 0));
    quad_.AddVertexAttribute(waterpine::GLVertexAttribute(vt, 2, kStride, (void *) kTexCoordOffset));
  }

  {
    const GLfloat vertices[] = {
        -32.0f, -32.0f, 0.0f, 0.0f,
        -32.0f, 32.0f, 0.0f, 1.0f,
        32.0f, -32.0f, 1.0f, 0.0f,
        32.0f, 32.0f, 1.0f, 1.0f,
    };
    quad_big_.SetBuffer(vertices, 4, 4);
    quad_big_.AddVertexAttribute(waterpine::GLVertexAttribute(vp, 2, kStride, 0));
    quad_big_.AddVertexAttribute(waterpine::GLVertexAttribute(vt, 2, kStride, (void *) kTexCoordOffset));
  }

  player_ship.LoadTexture(waterpine::OSUtils::GetResourcePath("ship", "png", "img"));
  enemy_turret.LoadTexture(waterpine::OSUtils::GetResourcePath("turret", "png", "img"));

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glViewport(0, 0, 640, 480);
}

void DrawFrame(void *arg) {
  GLFWwindow *window = static_cast<GLFWwindow *>(arg);

  glClear(GL_COLOR_BUFFER_BIT);

  sprite_shader.Apply();
  const auto loc = sprite_shader.GetUniformLocation("mMVP");

  wpmath::Mat44 mvp = kProjection * wpmath::MatrixTranslation(position);
  glUniformMatrix4fv(loc, 1, GL_FALSE, mvp.m);
  player_ship.Apply();
  quad_.Draw(GL_TRIANGLE_STRIP, 4);

  mvp = kProjection * wpmath::MatrixTranslation(turret_position);
  glUniformMatrix4fv(loc, 1, GL_FALSE, mvp.m);
  enemy_turret.Apply();
  quad_big_.Draw(GL_TRIANGLE_STRIP, 4);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
#ifdef __DESKTOP__
  if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }
#endif

  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_UP:
        position.y -= MoveStep;
        break;
      case GLFW_KEY_DOWN:
        position.y += MoveStep;
        break;
      case GLFW_KEY_LEFT:
        position.x -= MoveStep;
        break;
      case GLFW_KEY_RIGHT:
        position.x += MoveStep;
        break;
    }
  }
}

int main(void) {
  if (!glfwInit()) return -1;

  GLFWwindow *window = glfwCreateWindow(640, 480, "SSS01", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

#ifdef __DESKTOP__
  gladLoadGL();
#endif

  Init();

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(DrawFrame, window, 0, true);
#else
  while (!glfwWindowShouldClose(window)) {
    DrawFrame(window);
  }
#endif

  glfwTerminate();
  return 0;
}