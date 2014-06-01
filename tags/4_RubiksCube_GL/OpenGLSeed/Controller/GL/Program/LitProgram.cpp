#include "LitProgram.h"

namespace busybin
{
  /**
   * Set up the program.
   * @param name The name of the program
   */
  LitProgram::LitProgram(const string& name) : Program(name) {}

  /**
   * Install a positional light.
   * @param uniformName The name of the uniform positional light variable.
   * @param posLight A positional light.
   */
  void LitProgram::setUniform(const string& uniformName, const PositionalLight& posLight) const
  {
    this->setUniform(uniformName + ".position",             posLight.getPosition());
    this->setUniform(uniformName + ".ambient",              posLight.getAmbient());
    this->setUniform(uniformName + ".diffuse",              posLight.getDiffuse());
    this->setUniform(uniformName + ".specular",             posLight.getSpecular());
    this->setUniform(uniformName + ".constantAttenuation",  posLight.getConstantAttenuation());
    this->setUniform(uniformName + ".linearAttenuation",    posLight.getLinearAttenuation());
    this->setUniform(uniformName + ".quadraticAttenuation", posLight.getQuadraticAttenuation());
  }

  /**
   * Install a distance light.
   * @param uniformName The name of the uniform distance light variable.
   * @param distLight A distance light.
   */
  void LitProgram::setUniform(const string& uniformName, const DistanceLight& distLight) const
  {
    this->setUniform(uniformName + ".ambient",    distLight.getAmbient());
    this->setUniform(uniformName + ".diffuse",    distLight.getDiffuse());
    this->setUniform(uniformName + ".specular",   distLight.getSpecular());
    this->setUniform(uniformName + ".direction",  distLight.getDirection());
  }

  /**
   * Install a material.
   * @param uniformName The name of the uniform material variable.
   * @param material The material to install.
   */
  void LitProgram::setUniform(const string& uniformName, const Material& material) const
  {
    this->setUniform(uniformName + ".ambient",   material.getAmbient());
    this->setUniform(uniformName + ".diffuse",   material.getDiffuse());
    this->setUniform(uniformName + ".specular",  material.getSpecular());
    this->setUniform(uniformName + ".shininess", material.getShininess());
  }
}

