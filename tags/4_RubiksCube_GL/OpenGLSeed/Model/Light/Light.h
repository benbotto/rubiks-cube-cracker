#ifndef _BUSYBIN_LIGHT_H_
#define _BUSYBIN_LIGHT_H_

#define GLM_FORCE_RADIANS

#include "../../Controller/GL/Program/Program.h"
#include <string>
using std::string;
#include <glm/glm.hpp>
using glm::vec4;
#include <glm/gtc/type_ptr.hpp>
using glm::value_ptr;

namespace busybin
{
  /**
   * A basic Light class.
   */
  class Light
  {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

  public:
    Light(const vec4& ambient, const vec4& diffuse, const vec4& specular);
    vec4 getAmbient() const;
    vec4 getDiffuse() const;
    vec4 getSpecular() const;
  };
}

#endif

