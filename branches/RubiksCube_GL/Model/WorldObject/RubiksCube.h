#ifndef _BUSYBIN_RUBIKS_CUBE_H_
#define _BUSYBIN_RUBIKS_CUBE_H_

#include "Cubie.h"
#include "../../Controller/GL/Program/RubiksCubeProgram.h"
#include "../../OpenGLSeed/Model/WorldObject/WorldObject.h"
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
using glm::translate;
#include <map>
using std::map;
#include <memory>
using std::unique_ptr;

namespace busybin
{
  /**
   * An OpenGL RubiksCube.
   */
  class RubiksCube : public WorldObject
  {
    typedef unique_ptr<Cubie>      CubiePtr;
    typedef map<string, CubiePtr>  CubieMap;

    CubieMap cubies;

  public:
    RubiksCube(Program* pProgram, MatrixStack* pMatrixStack);
    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;
  };
}

#endif

