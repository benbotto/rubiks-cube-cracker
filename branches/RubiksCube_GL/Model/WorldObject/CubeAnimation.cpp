#include "RubiksCube.h"

namespace busybin
{
  /**
   * Animation for the whole cube.
   * @param rads The total radians to rotate.
   * @param axis The axis to rotate about, which should be normalized.
   */
  RubiksCube::CubeAnimation::CubeAnimation(double rads, const vec3& axis)
  {
    this->face = "";
    this->rads = rads;
    this->axis = axis;
  }

  /**
   * Animation for the whole cube.
   * @param face The RubiksCube face (e.g. "L" or "R").
   * @param rads The total radians to rotate.
   * @param axis The axis to rotate about, which should be normalized.
   */
  RubiksCube::CubeAnimation::CubeAnimation(const string& face,
    double rads, const vec3& axis)
  {
    this->face = face;
    this->rads = rads;
    this->axis = axis;
  }
}

