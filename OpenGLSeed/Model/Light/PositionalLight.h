#ifndef _BUSYBIN_POSITIONAL_LIGHT_H_
#define _BUSYBIN_POSITIONAL_LIGHT_H_

#include "Light.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;

namespace busybin
{
  /**
   * A basic PositionalLight class.
   */
  class PositionalLight : public Light
  {
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    vec3  position;

  public:
    PositionalLight(const vec4& ambient, const vec4& diffuse,
      const vec4& specular, float constantAttenuation,
      float linearAttenuation, float quadraticAttenuation,
      const vec3& position);

    float getConstantAttenuation() const;
    float getLinearAttenuation() const;
    float getQuadraticAttenuation() const;
    vec3 getPosition() const;
  };
}

#endif

