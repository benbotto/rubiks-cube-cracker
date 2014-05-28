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

namespace busybin
{
  /**
   * An example Cube.
   */
  class Cubie : public Cube
  {
    mat4 translation;

  public:
    Cubie(Program* pProgram, MatrixStack* pMatrixStack,
      const string& name, const vec3& position);
    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;
  };
}

#endif

