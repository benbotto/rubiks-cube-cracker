#include "RubiksCubeWorld.h"

namespace busybin
{
  /**
   * Init.
   * @param prog Unique pointer to the program.  Ownership is taken.
   */
  RubiksCubeWorld::RubiksCubeWorld(unique_ptr<Program> prog) : World(move(prog)),
    distLight(
      vec4( 1.0f,   1.0f,   1.0f, 1.0f), // Ambient.
      vec4( 1.0f,   1.0f,   1.0f, 1.0f), // Diffuse.
      vec4( 1.0f,   1.0f,   1.0f, 1.0f), // Specular.
      vec3(-100.0f, 55.0f, -50.0f))       // Direction.
  {
    this->getProgram().setUniform("ambient",   vec4(.8f, .8f, .8f, 1.0f));
    this->getProgram().setUniform("distLight", this->distLight);
    this->addWorldObject(woPtr(new RubiksCube(&this->getProgram(), &this->getMatrixStack())));

    //this->getCamera().setLocation(vec3(-10.0f, 10.0f, 10.0f));
    //this->getCamera().look();
  }

  /**
   * Get the program (down cast).
   */
  RubiksCubeProgram& RubiksCubeWorld::getProgram()
  {
    return dynamic_cast<RubiksCubeProgram&>(World::getProgram());
  }
}

