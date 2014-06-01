#ifndef _BUSYBIN_RUBIKS_CUBE_PROGRAM_H_
#define _BUSYBIN_RUBIKS_CUBE_PROGRAM_H_

#include "../../../OpenGLSeed/Controller/GL/Program/LitProgram.h"
#include <string>
using std::string;
#include <array>
using std::array;
#include <glm/gtc/type_ptr.hpp>
using glm::value_ptr;

namespace busybin
{
  /**
   * Example GLSL program.
   * be installed.
   */
  class RubiksCubeProgram : public LitProgram
  {
    int model;
    int view;
    int projection;
    int vertPos;
    int vertColor;
    int vertNormal;

  public:
    RubiksCubeProgram();
    int getModelAttr() const;
    int getViewAttr() const;
    int getProjectionAttr() const;
    int getVertexPositionAttr() const;
    int getVertexColorAttr() const;
    int getVertexNormalAttr() const;
  };
}

#endif
