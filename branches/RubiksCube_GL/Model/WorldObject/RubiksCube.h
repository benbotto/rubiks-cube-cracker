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
#include <queue>
using std::queue;
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
    /**
     * Helper class for the animation queue.
     */
    class CubeAnimation
    {
    public:
      string face;
      double rads;
      vec3   axis;

      CubeAnimation(double rads, const vec3& axis);
      CubeAnimation(const string& face, double rads, const vec3& axis);
    };

    typedef unique_ptr<Cubie>      CubiePtr;
    typedef map<string, CubiePtr>  CubieMap;

    CubieMap             cubies;
    double               amplitude;
    double               angle;
    double               angleDelta;
    mat4                 cubeRotation;
    queue<CubeAnimation> animationQueue;

    void animate(double elapsed);

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

