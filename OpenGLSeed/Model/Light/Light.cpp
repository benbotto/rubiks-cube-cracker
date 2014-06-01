#include "Light.h"

namespace busybin
{
  /**
   * Initialize the Light.
   * @param ambient The ambience of the Matieral.
   * @param diffuse How quickly light diffuses on the Light.
   * @param specular The mirror-like quality of the Light.
   */
  Light::Light(const vec4& ambient, const vec4& diffuse, const vec4& specular)
  {
    this->ambient  = ambient;
    this->diffuse  = diffuse;
    this->specular = specular;
  }

  /**
   * Get the ambience of the Light.
   */
  vec4 Light::getAmbient() const
  {
    return this->ambient;
  }

  /**
   * Get the diffuse of the Light.
   */
  vec4 Light::getDiffuse() const
  {
    return this->diffuse;
  }

  /**
   * Get the specular of the Light.
   */
  vec4 Light::getSpecular() const
  {
    return this->specular;
  }
}

