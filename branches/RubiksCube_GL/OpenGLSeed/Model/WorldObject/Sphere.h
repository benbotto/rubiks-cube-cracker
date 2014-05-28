#ifndef _BUSYBIN_SPHERE_H_
#define _BUSYBIN_SPHERE_H_

#include "WorldObject.h"
#include "../../Util/Inverter.h"
#include <algorithm>
using std::transform;
using std::copy;
using std::back_inserter;
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
#include <glm/gtc/constants.hpp> 
using glm::pi; 
using glm::half_pi;
#include <glm/gtc/matrix_transform.hpp>
using glm::rotate;

namespace busybin
{
  /**
   * A basic Sphere made from a series of triangles.
   */
  class Sphere : public WorldObject
  {
    float    radius;
    unsigned numTriangleStrips;

    void buildQuarterDome(vector<vec3>& vertBuf,
      vector<vec4>& colorBuf);

  public:
    Sphere(float radius, Program* pProgram, MatrixStack* pMatrixStack,
      const string& name = string("Sphere"), unsigned numTriangleStrips = 32,
      vector<vec4> colors = vector<vec4>(2, vec4(1.0f, 1.0f, 1.0f, 1.0f)));
  };
}

#endif

