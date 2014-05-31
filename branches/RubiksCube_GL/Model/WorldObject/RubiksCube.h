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
#include <array>
using std::array;
#include <memory>
using std::unique_ptr;
using std::move;
#include <cmath>
using std::cos;
#include <algorithm>
using std::swap;

namespace busybin
{
  /**
   * An OpenGL RubiksCube.
   */
  class RubiksCube : public WorldObject
  {
    typedef unique_ptr<Cubie>              CubiePtr;
    typedef map<string, CubiePtr>          CubieMap;
    typedef map<string, array<string, 9> > FaceMap;

    CubieMap cubies;
    FaceMap  faces;
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
    void moveFace(const array<string, 9>& face);
    void moveFacePrime(const array<string, 9>& face);

  public:
    RubiksCube(Program* pProgram, MatrixStack* pMatrixStack);

    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;

    void rotateLeft();
    void rotateRight();
    void rotateDown();
    void rotateUp();

    void u();
    void uPrime();
    void l();
    void lPrime();
    void f();
    void fPrime();
    void r();
    void rPrime();
    void b();
    void bPrime();
    void d();
    void dPrime();
  };
}

#endif

