#ifndef _BUSYBIN_MATERIAL_H_
#define _BUSYBIN_MATERIAL_H_

#define GLM_FORCE_RADIANS

#include "../../Controller/GL/Program/Program.h"
#include <glm/glm.hpp>
using glm::vec4;
#include <glm/gtc/type_ptr.hpp>
#include <string>
using std::string;

namespace busybin
{
  /**
   * A basic Material class, which describes the lighting properties of the
   * material.
   */
  class Material
  {
    string name;
    vec4   ambient;
    vec4   diffuse;
    vec4   specular;
    float  shininess;
  public:
    Material(const string& name, vec4 ambient, vec4 diffuse,
      vec4 specular, float shininess);

    string getName() const;
    vec4 getAmbient() const;
    vec4 getDiffuse() const;
    vec4 getSpecular() const;
    float getShininess() const;
  };
}

#endif

