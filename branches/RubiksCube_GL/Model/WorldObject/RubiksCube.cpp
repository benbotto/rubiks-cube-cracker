#include "RubiksCube.h"

namespace busybin
{
  /**
   * Initialize all of the cubies.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   */
  RubiksCube::RubiksCube(Program* pProgram, MatrixStack* pMatrixStack) : 
    WorldObject("RubiksCube", pProgram, pMatrixStack)
  {
    this->cubies["LDB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LDB", vec3(-1.0f, -1.0f, -1.0f)));
    this->cubies["LD"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LD",  vec3(-1.0f, -1.0f,  0.0f)));
    this->cubies["LDF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LDF", vec3(-1.0f, -1.0f,  1.0f)));
    this->cubies["LB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LB",  vec3(-1.0f,  0.0f, -1.0f)));
    this->cubies["L"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "L",   vec3(-1.0f,  0.0f,  0.0f)));
    this->cubies["LF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LF",  vec3(-1.0f,  0.0f,  1.0f)));
    this->cubies["LUB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LUB", vec3(-1.0f,  1.0f, -1.0f)));
    this->cubies["LU"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LU",  vec3(-1.0f,  1.0f,  0.0f)));
    this->cubies["LUF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LUF", vec3(-1.0f,  1.0f,  1.0f)));
    this->cubies["DB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "DB",  vec3( 0.0f, -1.0f, -1.0f)));
    this->cubies["D"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "D",   vec3( 0.0f, -1.0f,  0.0f)));
    this->cubies["DF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "DF",  vec3( 0.0f, -1.0f,  1.0f)));
    this->cubies["B"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "B",   vec3( 0.0f,  0.0f, -1.0f)));
    // No cubie in the middle.
    //this->cubies[""]    = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "", vec3( 0.0f,  0.0f,  0.0f)));
    this->cubies["F"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "F",   vec3( 0.0f,  0.0f,  1.0f)));
    this->cubies["UB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "UB",  vec3( 0.0f,  1.0f, -1.0f)));
    this->cubies["U"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "U",   vec3( 0.0f,  1.0f,  0.0f)));
    this->cubies["UF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "UF",  vec3( 0.0f,  1.0f,  1.0f)));
    this->cubies["RDB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RDB", vec3( 1.0f, -1.0f, -1.0f)));
    this->cubies["RD"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RD",  vec3( 1.0f, -1.0f,  0.0f)));
    this->cubies["RDF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RDF", vec3( 1.0f, -1.0f,  1.0f)));
    this->cubies["RB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RB",  vec3( 1.0f,  0.0f, -1.0f)));
    this->cubies["R"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "R",   vec3( 1.0f,  0.0f,  0.0f)));
    this->cubies["RF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RF",  vec3( 1.0f,  0.0f,  1.0f)));
    this->cubies["RUB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RUB", vec3( 1.0f,  1.0f, -1.0f)));
    this->cubies["RU"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RU",  vec3( 1.0f,  1.0f,  0.0f)));
    this->cubies["RUF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RUF", vec3( 1.0f,  1.0f,  1.0f)));
  }

  /**
   * Draw the all the cubies..
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void RubiksCube::draw(double elapsed)
  {
    for (CubieMap::iterator it = this->cubies.begin(); it != this->cubies.end(); ++it)
      it->second->draw(elapsed);
  }

  /**
   * Return the program (downcast).
   */
  RubiksCubeProgram* RubiksCube::getProgram() const
  {
    return dynamic_cast<RubiksCubeProgram*>(WorldObject::getProgram());
  }
}

