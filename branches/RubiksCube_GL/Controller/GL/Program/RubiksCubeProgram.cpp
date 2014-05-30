#include "RubiksCubeProgram.h"

namespace busybin
{
  /**
   * Initialize the program.
   */
  RubiksCubeProgram::RubiksCubeProgram() : LitProgram("OpenGL Seed Program")
  {
    // Set up the shaders.
    Shader fShader(
    {
      "./Shaders/version.h",
      "./Shaders/Material.h",
      "./Shaders/DistanceLight.h",
      "./Shaders/noise3D.h",
      "./Shaders/rubiksCube.frag"
    }, GL_FRAGMENT_SHADER);

    Shader vShader(
    {
      "./Shaders/version.h",
      "./Shaders/Material.h",
      "./Shaders/DistanceLight.h",
      "./Shaders/rubiksCube.vert"
    }, GL_VERTEX_SHADER);

    this->addShader(fShader);
    this->addShader(vShader);

    // Link and install the shaders.
    this->link();
    this->install();

    // Find and store the needed GLSL attributes.
    this->model      = this->findUniform("model");
    this->view       = this->findUniform("view");
    this->projection = this->findUniform("projection");
    this->vertPos    = this->findAttribute("vertPos");
    this->vertColor  = this->findAttribute("vertColor");
    this->vertNormal = this->findAttribute("vertNormal");
  }

  /**
   * Get the model attribute.
   */
  int RubiksCubeProgram::getModelAttr() const
  {
    return this->model;
  }

  /**
   * Get the view attribute.
   */
  int RubiksCubeProgram::getViewAttr() const
  {
    return this->view;
  }

  /**
   * Get the projection attribute.
   */
  int RubiksCubeProgram::getProjectionAttr() const
  {
    return this->projection;
  }

  /**
   * Get the vertex position attribute.
   */
  int RubiksCubeProgram::getVertexPositionAttr() const
  {
    return this->vertPos;
  }

  /**
   * Get the vertex color attribute.
   */
  int RubiksCubeProgram::getVertexColorAttr() const
  {
    return this->vertColor;
  }

  /**
   * Get the vertex normal attribute.
   */
  int RubiksCubeProgram::getVertexNormalAttr() const
  {
    return this->vertNormal;
  }
}

