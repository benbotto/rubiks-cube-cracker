#ifndef _BUSYBIN_MATRIX_STACK_H_
#define _BUSYBIN_MATRIX_STACK_H_

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
#include <stack>
using std::stack;

namespace busybin
{
  /**
   * This class is intended to replace the OpenGL 2 matrix stacks.  It
   * maintains separate model, view, and projection stacks.
   */
  class MatrixStack
  {
    stack<mat4> modelStack;
    stack<mat4> viewStack;
    stack<mat4> projectionStack;

    MatrixStack(const MatrixStack& m);
    void operator=(const MatrixStack& m);

  public:
    MatrixStack();

    void pushModel();
    void pushView();
    void pushProjection();
    void pushViewport();

    void popModel();
    void popView();
    void popProjection();
    void popViewport();

    mat4& topModel();
    mat4& topView();
    mat4& topProjection();

    const mat4& topModel() const;
    const mat4& topView() const;
    const mat4& topProjection() const;
  };
}

#endif
