#ifndef _BUSYBIN_DISTANCE_LIGHT_H_
#define _BUSYBIN_DISTANCE_LIGHT_H_

#include "Light.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;

namespace busybin
{
  /**
   * A basic DistanceLight class.
   */
  class DistanceLight : public Light
  {
    vec3 direction;

  public:
    DistanceLight(vec4 ambient, vec4 diffuse, vec4 specular, vec3 direction);
    vec3 getDirection() const;
  };
}

#endif

