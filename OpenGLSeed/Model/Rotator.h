#ifndef _BUSYBIN_ROTATOR_H_
#define _BUSYBIN_ROTATOR_H_

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
using glm::vec3;
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
using glm::rotate;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * An object that rotates around an arbitrary number of axises.
   * Rotations are applied from right to left (last in, first applied).
   */
  class Rotator
  {
    struct rotation
    {
      float radians;
      vec3  aboutAxis;
      mat4  rotation;
    };

    typedef vector<rotation> rotationVector;
    rotationVector rotations;

  public:
    Rotator();
    void addRotation(float radiansPerSecond, const vec3& aboutAxis);
    mat4 rotate(double elapsed);
  };
}

#endif

