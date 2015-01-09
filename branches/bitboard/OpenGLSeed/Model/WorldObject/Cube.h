#ifndef _BUSYBIN_CUBE_H_
#define _BUSYBIN_CUBE_H_

#include "WorldObject.h"
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * A basic Cube made from a series of triangles.
   */
  class Cube : public WorldObject
  {
    float size;

    void buildRect(const glm::vec3& topLeft, const glm::vec3& topRight,
      const glm::vec3& bottomLeft, const glm::vec3& bottomRight,
      vector<glm::vec3>& vertBuff);

  public:
    Cube(float size, Program* pProgram,
      MatrixStack* pMatrixStack, const string& name,
      vector<glm::vec4> colors = vector<glm::vec4>(6, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
  };
}

#endif
