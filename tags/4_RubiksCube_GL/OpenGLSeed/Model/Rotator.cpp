#include "Rotator.h"

namespace busybin
{
  /**
   * Initialize the Rotator.
   */
  Rotator::Rotator()
  {
  }

  /**
   * Add a rotation to the end of the rotations (applied last).
   * @param radiansPerSecond The amout to rotate per second.
   * @param aboutAxis The axis to rotate about.
   */
  void Rotator::addRotation(float radiansPerSecond, const vec3& aboutAxis)
  {
    rotation rot;

    rot.radians   = radiansPerSecond;
    rot.aboutAxis = aboutAxis;
    rot.rotation  = mat4(1.0f);

    rotations.push_back(rot);
  }

  /**
   * Get the transformation (rotations applied last to first).
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  mat4 Rotator::rotate(double elapsed)
  {
    mat4 final(1.0f);
    rotationVector::reverse_iterator end = rotations.rend();

    for (rotationVector::reverse_iterator rit = rotations.rbegin(); rit < end; ++rit)
    {
      rit->rotation = glm::rotate(rit->rotation, rit->radians * (float)elapsed, rit->aboutAxis);
      final *= rit->rotation;
    }

    return final;
  }
}

