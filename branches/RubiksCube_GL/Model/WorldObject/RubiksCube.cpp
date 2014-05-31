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
    // This is for the cube levitation effect (it bobs up and down).
    this->levitation.amplitude = 0.08f;
    this->levitation.angle     = 0.0f;
    this->levitation.delta     = pi<double>() * 2;

    // Cube rotation speed.
    this->cubeRot.speed = 8;

    // Tilt the cube by a constant amount so that the top, left, and front
    // are always visible.
    this->cubeTilt = rotate(mat4(1.0f),     pi<float>() / 9, vec3(1.0f, 0.0f, 0.0f));
    this->cubeTilt = rotate(this->cubeTilt, pi<float>() / 6, vec3(0.0f, 1.0f, 0.0f));

    // Initialize the cubies.
    this->cubies["LDB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LDB", vec3(-1.02f, -1.02f, -1.02f)));
    this->cubies["LD"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LD",  vec3(-1.02f, -1.02f,  0.0f)));
    this->cubies["LDF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LDF", vec3(-1.02f, -1.02f,  1.02f)));
    this->cubies["LB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LB",  vec3(-1.02f,  0.0f,  -1.02f)));
    this->cubies["L"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "L",   vec3(-1.02f,  0.0f,   0.0f)));
    this->cubies["LF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LF",  vec3(-1.02f,  0.0f,   1.02f)));
    this->cubies["LUB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LUB", vec3(-1.02f,  1.02f, -1.02f)));
    this->cubies["LU"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LU",  vec3(-1.02f,  1.02f,  0.0f)));
    this->cubies["LUF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "LUF", vec3(-1.02f,  1.02f,  1.02f)));
    this->cubies["DB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "DB",  vec3( 0.0f,  -1.02f, -1.02f)));
    this->cubies["D"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "D",   vec3( 0.0f,  -1.02f,  0.0f)));
    this->cubies["DF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "DF",  vec3( 0.0f,  -1.02f,  1.02f)));
    this->cubies["B"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "B",   vec3( 0.0f,   0.0f,  -1.02f)));
    // No cubie in the middle.
    //this->cubies[""]    = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "", vec3( 0.0f,  0.0f,  0.0f)));
    this->cubies["F"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "F",   vec3( 0.0f,   0.0f,   1.02f)));
    this->cubies["UB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "UB",  vec3( 0.0f,   1.02f, -1.02f)));
    this->cubies["U"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "U",   vec3( 0.0f,   1.02f,  0.0f)));
    this->cubies["UF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "UF",  vec3( 0.0f,   1.02f,  1.02f)));
    this->cubies["RDB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RDB", vec3( 1.02f, -1.02f, -1.02f)));
    this->cubies["RD"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RD",  vec3( 1.02f, -1.02f,  0.0f)));
    this->cubies["RDF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RDF", vec3( 1.02f, -1.02f,  1.02f)));
    this->cubies["RB"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RB",  vec3( 1.02f,  0.0f,  -1.02f)));
    this->cubies["R"]   = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "R",   vec3( 1.02f,  0.0f,   0.0f)));
    this->cubies["RF"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RF",  vec3( 1.02f,  0.0f,   1.02f)));
    this->cubies["RUB"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RUB", vec3( 1.02f,  1.02f, -1.02f)));
    this->cubies["RU"]  = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RU",  vec3( 1.02f,  1.02f,  0.0f)));
    this->cubies["RUF"] = CubiePtr(new Cubie(this->getProgram(), this->getMatrixStack(), "RUF", vec3( 1.02f,  1.02f,  1.02f)));
  }

  /**
   * Draw the all the cubies..
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void RubiksCube::draw(double elapsed)
  {
    mat4 cubeRotation;

    // Make the cube bob up and down like it's levitating.
    this->levitation.angle   += this->levitation.delta * elapsed;
    this->levitation.transBy  = this->levitation.amplitude * cos(this->levitation.angle);
    this->levitation.trans    = translate(mat4(1.0f), vec3(0.0f, this->levitation.transBy, 0.0f));

    // Animate any queued up cube rotations.
    cubeRotation = this->animateCubeRotation(elapsed);
    this->getMatrixStack()->topModel() = this->levitation.trans * this->cubeTilt * cubeRotation;

    // Draw each cube.
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

  /**
   * Animate the cube rotations.
   * @param elapsed The elapsed time since the last draw call.
   */
  mat4 RubiksCube::animateCubeRotation(double elapsed)
  {
    // Spherical linear interpolation (SLERP) between the current and desired
    // orientations.
    this->cubeRot.orientation = slerp(this->cubeRot.orientation,
      this->cubeRot.desired, this->cubeRot.speed * (float)elapsed);

    return mat4_cast(this->cubeRot.orientation);
  }

  /**
   * Rotate the whole cube left.
   */
  void RubiksCube::rotateLeft()
  {
    this->cubeRot.desired = rotate(quat(), half_pi<float>() * -1,
      vec3(0.0f, 1.0f, 0.0f)) * this->cubeRot.desired;
  }

  /**
   * Rotate the whole cube right.
   */
  void RubiksCube::rotateRight()
  {
    this->cubeRot.desired = rotate(quat(), half_pi<float>(),
      vec3(0.0f, 1.0f, 0.0f)) * this->cubeRot.desired;
  }

  /**
   * Rotate the whole cube down.
   */
  void RubiksCube::rotateDown()
  {
    this->cubeRot.desired = rotate(quat(), half_pi<float>(),
      vec3(1.0f, 0.0f, 0.0f)) * this->cubeRot.desired;
  }

  /**
   * Rotate the whole cube up.
   */
  void RubiksCube::rotateUp()
  {
    this->cubeRot.desired = rotate(quat(), half_pi<float>() * -1,
      vec3(1.0f, 0.0f, 0.0f)) * this->cubeRot.desired;
  }
}

