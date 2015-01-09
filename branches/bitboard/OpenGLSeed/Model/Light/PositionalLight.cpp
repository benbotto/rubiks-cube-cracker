#include "PositionalLight.h"

namespace busybin
{
  /**
   * Initialize the PositionalLight.
   * @param ambient The ambience of the Matieral.
   * @param diffuse How quickly light diffuses on the PositionalLight.
   * @param specular The mirror-like quality of the PositionalLight.
   * @param constantAttenuation The constant attenuation of the light.
   * @param linearAttenuation The linear attenuation of the light.
   * @param quadraticAttenuation The quadratic attenuation of the light.
   * @param position The position of the light.
   */
  PositionalLight::PositionalLight(const vec4& ambient, const vec4& diffuse,
    const vec4& specular, float constantAttenuation,
    float linearAttenuation,  float quadraticAttenuation,
    const vec3& position) :
    Light(ambient, diffuse, specular)
  {
    this->position             = position;
    this->constantAttenuation  = constantAttenuation;
    this->linearAttenuation    = linearAttenuation;
    this->quadraticAttenuation = quadraticAttenuation;
  }

  /**
   * Get the position of the PositionalLight.
   */
  vec3 PositionalLight::getPosition() const
  {
    return this->position;
  }

  /**
   * Get the constant attenuation.
   */
  float PositionalLight::getConstantAttenuation() const
  {
    return this->constantAttenuation;
  }

  /**
   * Get the linear attenuation.
   */
  float PositionalLight::getLinearAttenuation() const
  {
    return this->linearAttenuation;
  }

  /**
   * Get the quadratic attenuation.
   */
  float PositionalLight::getQuadraticAttenuation() const
  {
    return this->quadraticAttenuation;
  }
}

