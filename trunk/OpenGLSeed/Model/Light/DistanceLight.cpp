#include "DistanceLight.h"

namespace busybin
{
  /**
   * Initialize the DistanceLight.
   * @param ambient The ambience of the Matieral.
   * @param diffuse How quickly light diffuses on the DistanceLight.
   * @param specular The mirror-like quality of the DistanceLight.
   * @param direction The direction of the light.
   */
  DistanceLight::DistanceLight(vec4 ambient, vec4 diffuse, vec4 specular, vec3 direction) :
    Light(ambient, diffuse, specular)
  {
    this->direction = direction;
  }

  /**
   * Get the direction of the DistanceLight.
   */
  vec3 DistanceLight::getDirection() const
  {
    return direction;
  }
}

