#ifndef _BUSYBIN_CUBIE_H_
#define _BUSYBIN_CUBIE_H_

#include "../../OpenGLSeed/Model/WorldObject/Cube.h"
#include "../../OpenGLSeed/Model/Material/GrayPlastic.h"
#include "../../Controller/GL/Program/RubiksCubeProgram.h"
#include <glm/gtc/constants.hpp>
using glm::half_pi;
#include <glm/glm.hpp>
using glm::vec4;
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
using glm::translate;
#include <glm/gtc/quaternion.hpp>
using glm::quat;
using glm::slerp;
using glm::mat4_cast;
using glm::normalize;
using glm::dot;
#include <cmath>
using std::fabs;

namespace busybin
{
  /**
   * An example Cube.
   */
  class Cubie : public Cube
  {
    mat4 translation;
    bool superGlow;

    // For rotating the cubie.
    struct
    {
      quat  orientation;
      quat  desired;
      float speed;
    } cubeRot;

    mat4 animateCubeRotation(double elapsed);

  public:
    Cubie(Program* pProgram, MatrixStack* pMatrixStack,
      const string& name, const vec3& position);
    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;

    void rotate(float rads, const vec3& axis);
    void setSuperGlow(bool superGlow);
  };
}

#endif

