#ifndef _BUSYBIN_TORUS_H_
#define _BUSYBIN_TORUS_H_

#include "WorldObject.h"
#include <glm/gtc/constants.hpp> 
using glm::pi; 
#include <glm/gtc/matrix_transform.hpp>
using glm::rotate;
using glm::translate;

namespace busybin
{
  /**
   * A basic Torus.
   */
  class Torus : public WorldObject
  {
  public:
    Torus(float innerRadius, float outerRadius, Program* pProgram,
      MatrixStack* pMatrixStack, const string& name = "Torus",
      unsigned numTriangleStrips = 32,
      vector<glm::vec4> colors = vector<glm::vec4>(4, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
  };
}

#endif

