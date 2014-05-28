#include "Orbiter.h"

namespace busybin
{
  /**
   * Initialize the orbiter.
   * @param radiansPerSecond The number of degrees to orbit each draw.
   * @param translateTo The position to translate the object to 
   * prior to rotation.
   * @param aboutAxis The axis to orbit about.
   */
  Orbiter::Orbiter(float radiansPerSecond, vec3 translateTo, vec3 aboutAxis) : 
    translation(1.0f), rotation(1.0f), axis(aboutAxis)
  {
    this->setRadiansPerSecond(radiansPerSecond);
    this->setTranslateTo(translateTo);
  }

  /**
   * Get the number of degrees this orbiter rotates per draw.
   */
  float Orbiter::getRadiansPerSecond() const
  {
    return this->radiansPerSecond;
  }

  /**
   * Change the speed at which this moon orbits its planet.
   * @param radiansPerSecond The number of degrees to orbit each draw.
   */
  void Orbiter::setRadiansPerSecond(float radiansPerSecond)
  {
    this->radiansPerSecond = radiansPerSecond;
  }

  /**
   * Set the initial translat position.
   * @param translateTo The position to translate the object to prior
   * to rotating it.  The length of this vector is the orbit radius.
   */
  void Orbiter::setTranslateTo(vec3 translateTo)
  {
    this->translation = translate(mat4(1.0f), translateTo);
  }

  /**
   * Get the axis that this object orbits about.
   */
  vec3 Orbiter::getAboutAxis() const
  {
    return this->axis;
  }

  /**
   * Change the radius that this object rotates about.
   * @param aboutAxis The axis to rotate about.
   */
  void Orbiter::setAboutAxis(vec3 aboutAxis)
  {
    this->axis = aboutAxis;
  }

  /**
   * Apply the orbit (translation * currentOrbit).
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  mat4 Orbiter::orbit(double elapsed)
  {
    this->rotation = rotate(this->rotation,
      this->getRadiansPerSecond() * (float)elapsed, this->getAboutAxis());

    return this->rotation * this->translation;
  }
}

