#ifndef _BUSYBIN_RUBIKS_CUBE_WORLD_OBJECT_H_
#define _BUSYBIN_RUBIKS_CUBE_WORLD_OBJECT_H_

#include "Cubie.h"
#include "../../Controller/GL/Program/RubiksCubeProgram.h"
#include "../../OpenGLSeed/Model/WorldObject/WorldObject.h"
#include "../RubiksCube.h"
#include "../RubiksCubeModel.h"
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
  class RubiksCubeWorldObject : public WorldObject, public RubiksCube
  {
    typedef unique_ptr<Cubie>              CubiePtr;
    typedef map<string, CubiePtr>          CubieMap;
    typedef map<string, array<string, 9> > FaceMap;
    typedef map<string, array<string, 8> > SliceMap;

    CubieMap        cubies;
    FaceMap         faces;
    SliceMap        slices;
    mat4            cubeTilt;
    RubiksCubeModel rawCubeModel;

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
    RubiksCubeWorldObject(Program* pProgram, MatrixStack* pMatrixStack);

    void draw(double elapsed);
    RubiksCubeProgram* getProgram() const;

    RubiksCubeModel getRawModel() const;

    COLOR getColor(FACE face, unsigned row, unsigned col) const;

    bool isSolved() const;

    RubiksCube& x();
    RubiksCube& xPrime();
    RubiksCube& x2();

    RubiksCube& y();
    RubiksCube& yPrime();
    RubiksCube& y2();

    RubiksCube& z();
    RubiksCube& zPrime();
    RubiksCube& z2();

    RubiksCube& u();
    RubiksCube& uPrime();
    RubiksCube& u2();

    RubiksCube& l();
    RubiksCube& lPrime();
    RubiksCube& l2();

    RubiksCube& f();
    RubiksCube& fPrime();
    RubiksCube& f2();

    RubiksCube& r();
    RubiksCube& rPrime();
    RubiksCube& r2();

    RubiksCube& b();
    RubiksCube& bPrime();
    RubiksCube& b2();

    RubiksCube& d();
    RubiksCube& dPrime();
    RubiksCube& d2();

    RubiksCube& m();
    RubiksCube& mPrime();
    RubiksCube& m2();

    RubiksCube& e();
    RubiksCube& ePrime();
    RubiksCube& e2();

    RubiksCube& s();
    RubiksCube& sPrime();
    RubiksCube& s2();
  };
}

#endif

