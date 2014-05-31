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
using glm::rotate;
#include <glm/gtc/constants.hpp> 
using glm::pi;
using glm::half_pi;
#include <glm/gtc/quaternion.hpp>
using glm::quat;
using glm::slerp;
using glm::mat4_cast;
#include <map>
using std::map;
#include <memory>
using std::unique_ptr;
#include <cmath>
using std::cos;

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
    mat4     cubeTilt;

    // For rotating the cube.
    struct
    {
      quat  orientation;
      quat  desired;
      float speed;
    } cubeRot;

    // For bobbing the cube up and down (levitation).
    struct
    {
      double amplitude;
      double angle;
      double delta;
      double transBy;
      mat4   trans;
    } levitation;

    mat4 animateCubeRotation(double elapsed);

  public:
    RubiksCube(Program* pProgram, MatrixStack* pMatrixStack);

    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;

    void rotateLeft();
    void rotateRight();
    void rotateDown();
    void rotateUp();
  };
}

#endif

