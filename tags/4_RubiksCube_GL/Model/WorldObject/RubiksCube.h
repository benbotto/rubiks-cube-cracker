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
    typedef map<string, array<string, 8> > SliceMap;

    CubieMap cubies;
    FaceMap  faces;
    SliceMap slices;
    mat4     cubeTilt;

    // For bobbing the cube up and down (levitation).
    struct
    {
      double amplitude;
      double angle;
      double delta;
      double transBy;
      mat4   trans;
    } levitation;

    void moveFace(const array<string, 9>& face);
    void moveFacePrime(const array<string, 9>& face);
    void moveSlice(const array<string, 8>& slice);
    void moveSlicePrime(const array<string, 8>& slice);

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
    void u2();

    void l();
    void lPrime();
    void l2();

    void f();
    void fPrime();
    void f2();

    void r();
    void rPrime();
    void r2();

    void b();
    void bPrime();
    void b2();

    void d();
    void dPrime();
    void d2();

    void m();
    void mPrime();
    void m2();

    void e();
    void ePrime();
    void e2();

    void s();
    void sPrime();
    void s2();
  };
}

#endif

