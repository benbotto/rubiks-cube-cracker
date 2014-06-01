#include "MatrixStack.h"

namespace busybin
{
  /**
   * Initialize the MatrixStack with identity matrixes.
   */
  MatrixStack::MatrixStack()
  {
    this->modelStack.push(mat4(1.0f));
    this->viewStack.push(mat4(1.0f));
    this->projectionStack.push(mat4(1.0f));
  }

  /**
   * Prevent copies.
   * @param m Not used.
   */
  MatrixStack::MatrixStack(const MatrixStack& m) {}

  /**
   * Prevent copies.
   * @param m Not used.
   */
  void MatrixStack::operator=(const MatrixStack& m) {}

  /**
   * Copies the top element of the model matrix and pushes it on to the stack.
   */
  void MatrixStack::pushModel()
  {
    mat4 top = this->modelStack.top();
    this->modelStack.push(top);
  }

  /**
   * Copies the top element of the view matrix and pushes it on to the stack.
   */
  void MatrixStack::pushView()
  {
    mat4 top = this->viewStack.top();
    this->viewStack.push(top);
  }

  /**
   * Copies the top element of the projection matrix and pushes it on to the stack.
   */
  void MatrixStack::pushProjection()
  {
    mat4 top = this->projectionStack.top();
    this->projectionStack.push(top);
  }

  /**
   * Pop the top element of the stack.
   */
  void MatrixStack::popModel()
  {
    this->modelStack.pop();
  }

  /**
   * Pop the top element of the stack.
   */
  void MatrixStack::popView()
  {
    this->viewStack.pop();
  }

  /**
   * Pop the top element of the stack.
   */
  void MatrixStack::popProjection()
  {
    this->projectionStack.pop();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  mat4& MatrixStack::topModel()
  {
    return this->modelStack.top();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  mat4& MatrixStack::topView()
  {
    return this->viewStack.top();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  mat4& MatrixStack::topProjection()
  {
    return this->projectionStack.top();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  const mat4& MatrixStack::topModel() const
  {
    return this->modelStack.top();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  const mat4& MatrixStack::topView() const
  {
    return this->viewStack.top();
  }

  /**
   * Get a reference to the top element of the stack.
   */
  const mat4& MatrixStack::topProjection() const
  {
    return this->projectionStack.top();
  }
}

