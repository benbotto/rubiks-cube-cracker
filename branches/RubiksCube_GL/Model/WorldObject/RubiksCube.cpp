#include "RubiksCube.h"

namespace busybin
{
  /**
   * Initialize all of the cubies.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   */
  RubiksCube::RubiksCube(Program* pProgram, MatrixStack* pMatrixStack) : 
    WorldObject("RubiksCube", pProgram, pMatrixStack), cubeRotation(1.0f)
  {
    this->amplitude    = 0.08f;
    this->angle        = 0.0f;
    this->angleDelta   = pi<double>() * 2;

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
    double transBy;
    mat4   translation;

    // Make the cube bob up and down like it's levitating.
    this->angle += this->angleDelta * elapsed;
    transBy = this->amplitude * cos(this->angle);
    translation = translate(mat4(1.0f), vec3(0.0f, transBy, 0.0f));

    // Animate any queued up rotations.
    this->animate(elapsed);

    this->getMatrixStack()->topModel() = translation * this->cubeRotation;

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
   * Process the top-most animation in the animation queue.
   * @param elapsed The elapsed time since the last draw call.
   */
  void RubiksCube::animate(double elapsed)
  {
    if (!this->animationQueue.empty())
    {
      CubeAnimation& anim  = this->animationQueue.front();
      vec3           axis  = anim.axis;
      int            dir   = (anim.rads > 0) ? -1 : 1;
      float          delta = this->angleDelta * elapsed * dir;
      bool           done  = false;

      // Change the animation radians based on the elapsed time until
      // 0 is reached.
      if ((dir == 1 && anim.rads + delta > 0) || (dir == -1 && anim.rads + delta < 0))
      {
        delta = anim.rads * -1;
        this->animationQueue.pop();
      }
      else
        anim.rads += delta;

      // Move the whole cube.
      if (anim.face == "")
      {
        //this->cubeRotation *= rotate(mat4(1.0f), delta, axis);
        this->cubeRotation = rotate(mat4(1.0f), delta, axis) * this->cubeRotation;
      }

      // If this animation is complete remove it from the queue.
      if (done)
        this->animationQueue.pop();
    }
  }

  /**
   * Rotate the whole cube left.
   */
  void RubiksCube::rotateLeft()
  {
    this->animationQueue.push(CubeAnimation(half_pi<float>(), vec3(0.0f, 1.0f, 0.0f)));
  }

  /**
   * Rotate the whole cube right.
   */
  void RubiksCube::rotateRight()
  {
    this->animationQueue.push(CubeAnimation(half_pi<float>() * -1, vec3(0.0f, 1.0f, 0.0f)));
  }

  /**
   * Rotate the whole cube down.
   */
  void RubiksCube::rotateDown()
  {
    this->animationQueue.push(CubeAnimation(half_pi<float>() * -1, vec3(1.0f, 0.0f, 0.0f)));
  }

  /**
   * Rotate the whole cube up.
   */
  void RubiksCube::rotateUp()
  {
    this->animationQueue.push(CubeAnimation(half_pi<float>(), vec3(1.0f, 0.0f, 0.0f)));
  }
}

