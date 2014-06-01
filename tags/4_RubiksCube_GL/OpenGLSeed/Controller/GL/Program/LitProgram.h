#ifndef _BUSYBIN_LIT_PROGRAM_H_
#define _BUSYBIN_LIT_PROGRAM_H_

#include "Program.h"
#include "../../../Model/Light/PositionalLight.h"
#include "../../../Model/Light/DistanceLight.h"
#include "../../../Model/Material/Material.h"
#include <glm/glm.hpp>
using glm::mat4;

namespace busybin
{
  /**
   * A program that allows for setting a material and various types of lights.
   */
  class LitProgram : public Program
  {
    bool lightOn;
    vec4 ambientLight;

  public:
    // Don't hide Program's setUniform overloads.
    using Program::setUniform;

    LitProgram(const string& name);

    void setUniform(const string& uniformName, const PositionalLight& posLight) const;
    void setUniform(const string& uniformName, const DistanceLight& distLight) const;
    void setUniform(const string& uniformName, const Material& material) const;
  };
}

#endif
