#include "VectorHelper.h"

namespace busybin
{
  /**
   * Print a vector.
   * @param vec The vector to print.
   */
  void VectorHelper::printVec(const vec3& vec)
  {
    cout << std::setprecision(10) << fixed
         << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << endl;
  }

  /**
   * Check if two vectors are equal.
   * @param v1 The first vector to compare.
   * @param v2 The second vector to compare.
   */
  bool VectorHelper::equal(const vec3& v1, const vec3& v2)
  {
    const float epsilon = .0001;
    vec3 diff = abs(v1 - v2);

    return diff.x < epsilon && diff.y < epsilon && diff.z < epsilon;
  }

  /**
   * Check if a vector is less than another (i.e. one of the values is
   * less than another).
   * @param v1 The first vector to compare.
   * @param v2 The second vector to compare.
   */
  bool VectorHelper::lessThan(const vec3& v1, const vec3& v2)
  {
    const float epsilon = .0001;

    if (fabs(v1.x - v2.x) > epsilon)
      return v1.x < v2.x;

    if (fabs(v1.y - v2.y) > epsilon)
      return v1.y < v2.y;

    if (fabs(v1.z - v2.z) > epsilon)
      return v1.z < v2.z;

    return false;
  }
}

