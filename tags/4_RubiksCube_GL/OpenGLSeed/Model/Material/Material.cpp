#include "Material.h"

namespace busybin
{
  /**
   * Initialize the Material.
   * @param name The name of the Material.
   * @param ambient The ambience of the Matieral.
   * @param diffuse How quickly light diffuses on the Material.
   * @param specular The mirror-like quality of the Material.
   * @param shininess How shiny the Material is.
   * GL_FRAGMENT_SHADER)
   */
  Material::Material(const string& name, vec4 ambient, vec4 diffuse,
    vec4 specular, float shininess)
  {
    this->name      = name;
    this->ambient   = ambient;
    this->diffuse   = diffuse;
    this->specular  = specular;
    this->shininess = shininess;
  }

  /**
   * Get the name of the Material.
   */
  string Material::getName() const
  {
    return this->name;
  }

  /**
   * Get the ambience of the Material.
   */
  vec4 Material::getAmbient() const
  {
    return this->ambient;
  }

  /**
   * Get the diffuse of the Material.
   */
  vec4 Material::getDiffuse() const
  {
    return this->diffuse;
  }

  /**
   * Get the specular of the Material.
   */
  vec4 Material::getSpecular() const
  {
    return this->specular;
  }

  /**
   * Get the shininess of the Material.
   */
  float Material::getShininess() const
  {
    return this->shininess;
  }
}

