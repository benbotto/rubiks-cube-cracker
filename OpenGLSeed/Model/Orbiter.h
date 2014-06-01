#ifndef _BUSYBIN_ORBITER_H_
#define _BUSYBIN_ORBITER_H_

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
using glm::vec3;
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
using glm::rotate;
using glm::translate;

namespace busybin
{
  /**
   * A thing that can orbit (planet, moon, etc).
   */
  class Orbiter
  {
    float radiansPerSecond;
    mat4  translation;
    mat4  rotation;
    vec3  axis;

  public:
    Orbiter(float radiansPerSecond, vec3 translateTo, vec3 aboutAxis);

    float getRadiansPerSecond() const;
    void setRadiansPerSecond(float radiansPerSecond);
    void setTranslateTo(vec3 translateTo);
    vec3 getAboutAxis() const;
    void setAboutAxis(vec3 aboutAxis);

    mat4 orbit(double elapsed);
  };
}

#endif
