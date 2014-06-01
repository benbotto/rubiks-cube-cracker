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
    RubiksCubeProgram* p = this->getProgram();
    MatrixStack*       m = this->getMatrixStack();

    // This is for the cube levitation effect (it bobs up and down).
    this->levitation.amplitude = 0.08f;
    this->levitation.angle     = 0.0f;
    this->levitation.delta     = pi<double>() * 2;

    // Tilt the cube by a constant amount so that the top, left, and front
    // are always visible.
    this->cubeTilt = rotate(mat4(1.0f),     pi<float>() / 9, vec3(1.0f, 0.0f, 0.0f));
    this->cubeTilt = rotate(this->cubeTilt, pi<float>() / 6, vec3(0.0f, 1.0f, 0.0f));

    // Initialize the cubies.  There is no cubie in the middle (at 0,0,0).
    // The pneumonic refers to the position of the cubie and is kept
    // in tact after rotations.
    this->cubies["LDB"] = CubiePtr(new Cubie(p, m, "LDB", vec3(-1.02f, -1.02f, -1.02f)));
    this->cubies["LD"]  = CubiePtr(new Cubie(p, m, "LD",  vec3(-1.02f, -1.02f,  0.0f)));
    this->cubies["LDF"] = CubiePtr(new Cubie(p, m, "LDF", vec3(-1.02f, -1.02f,  1.02f)));
    this->cubies["LB"]  = CubiePtr(new Cubie(p, m, "LB",  vec3(-1.02f,  0.0f,  -1.02f)));
    this->cubies["L"]   = CubiePtr(new Cubie(p, m, "L",   vec3(-1.02f,  0.0f,   0.0f)));
    this->cubies["LF"]  = CubiePtr(new Cubie(p, m, "LF",  vec3(-1.02f,  0.0f,   1.02f)));
    this->cubies["LUB"] = CubiePtr(new Cubie(p, m, "LUB", vec3(-1.02f,  1.02f, -1.02f)));
    this->cubies["LU"]  = CubiePtr(new Cubie(p, m, "LU",  vec3(-1.02f,  1.02f,  0.0f)));
    this->cubies["LUF"] = CubiePtr(new Cubie(p, m, "LUF", vec3(-1.02f,  1.02f,  1.02f)));
    this->cubies["DB"]  = CubiePtr(new Cubie(p, m, "DB",  vec3( 0.0f,  -1.02f, -1.02f)));
    this->cubies["D"]   = CubiePtr(new Cubie(p, m, "D",   vec3( 0.0f,  -1.02f,  0.0f)));
    this->cubies["DF"]  = CubiePtr(new Cubie(p, m, "DF",  vec3( 0.0f,  -1.02f,  1.02f)));
    this->cubies["B"]   = CubiePtr(new Cubie(p, m, "B",   vec3( 0.0f,   0.0f,  -1.02f)));
    //this->cubies[""]    = CubiePtr(new Cubie(p, m, "", vec3( 0.0f,  0.0f,  0.0f)));
    this->cubies["F"]   = CubiePtr(new Cubie(p, m, "F",   vec3( 0.0f,   0.0f,   1.02f)));
    this->cubies["UB"]  = CubiePtr(new Cubie(p, m, "UB",  vec3( 0.0f,   1.02f, -1.02f)));
    this->cubies["U"]   = CubiePtr(new Cubie(p, m, "U",   vec3( 0.0f,   1.02f,  0.0f)));
    this->cubies["UF"]  = CubiePtr(new Cubie(p, m, "UF",  vec3( 0.0f,   1.02f,  1.02f)));
    this->cubies["RDB"] = CubiePtr(new Cubie(p, m, "RDB", vec3( 1.02f, -1.02f, -1.02f)));
    this->cubies["RD"]  = CubiePtr(new Cubie(p, m, "RD",  vec3( 1.02f, -1.02f,  0.0f)));
    this->cubies["RDF"] = CubiePtr(new Cubie(p, m, "RDF", vec3( 1.02f, -1.02f,  1.02f)));
    this->cubies["RB"]  = CubiePtr(new Cubie(p, m, "RB",  vec3( 1.02f,  0.0f,  -1.02f)));
    this->cubies["R"]   = CubiePtr(new Cubie(p, m, "R",   vec3( 1.02f,  0.0f,   0.0f)));
    this->cubies["RF"]  = CubiePtr(new Cubie(p, m, "RF",  vec3( 1.02f,  0.0f,   1.02f)));
    this->cubies["RUB"] = CubiePtr(new Cubie(p, m, "RUB", vec3( 1.02f,  1.02f, -1.02f)));
    this->cubies["RU"]  = CubiePtr(new Cubie(p, m, "RU",  vec3( 1.02f,  1.02f,  0.0f)));
    this->cubies["RUF"] = CubiePtr(new Cubie(p, m, "RUF", vec3( 1.02f,  1.02f,  1.02f)));

    // Initialize the faces.
    this->faces["U"] = {{"LUB", "UB", "RUB", "LU", "U", "RU", "LUF", "UF", "RUF"}};
    this->faces["L"] = {{"LUB", "LU", "LUF", "LB", "L", "LF", "LDB", "LD", "LDF"}};
    this->faces["F"] = {{"LUF", "UF", "RUF", "LF", "F", "RF", "LDF", "DF", "RDF"}};
    this->faces["R"] = {{"RUF", "RU", "RUB", "RF", "R", "RB", "RDF", "RD", "RDB"}};
    this->faces["B"] = {{"RUB", "UB", "LUB", "RB", "B", "LB", "RDB", "DB", "LDB"}};
    this->faces["D"] = {{"LDF", "DF", "RDF", "LD", "D", "RD", "LDB", "DB", "RDB"}};

    // Initialize the slices.
    this->slices["M"] = {{"UB", "U", "UF", "F", "DF", "D", "DB", "B"}};
    this->slices["E"] = {{"LB", "L", "LF", "F", "RF", "R", "RB", "B"}};
    this->slices["S"] = {{"LU", "U", "RU", "R", "RD", "D", "LD", "L"}};
  }

  /**
   * Draw the all the cubies.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void RubiksCube::draw(double elapsed)
  {
    // Make the cube bob up and down like it's levitating.
    this->levitation.angle   += this->levitation.delta * elapsed;
    this->levitation.transBy  = this->levitation.amplitude * cos(this->levitation.angle);
    this->levitation.trans    = translate(mat4(1.0f), vec3(0.0f, this->levitation.transBy, 0.0f));

    // Move the levitation and the tilt to the top of the stack.
    this->getMatrixStack()->topModel() = this->levitation.trans * this->cubeTilt;

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
   * When a face is rotated, the indices need to be shuffled around.  For
   * example, with an U rotation, LUF is moved to LUB.
   * @param face The face to rotate clockwise.
   */
  void RubiksCube::moveFace(const array<string, 9>& face)
  {
    array<CubiePtr, 9> hold;

    // Copy all the cubie pointers.
    for (unsigned i = 0; i < 9; ++i)
      hold[i] = move(this->cubies.at(face[i]));

    // Corners.
    this->cubies.at(face[0]) = move(hold.at(6));
    this->cubies.at(face[2]) = move(hold.at(0));
    this->cubies.at(face[6]) = move(hold.at(8));
    this->cubies.at(face[8]) = move(hold.at(2));

    // Edges.
    this->cubies.at(face[1]) = move(hold.at(3));
    this->cubies.at(face[3]) = move(hold.at(7));
    this->cubies.at(face[5]) = move(hold.at(1));
    this->cubies.at(face[7]) = move(hold.at(5));

    // Center.
    this->cubies.at(face[4]) = move(hold.at(4));
  }

  /**
   * See moveFace.  Same thing but prime.
   * @param face The face to rotate counter-clockwise.
   */
  void RubiksCube::moveFacePrime(const array<string, 9>& face)
  {
    array<CubiePtr, 9> hold;

    // Copy all the cubie pointers.
    for (unsigned i = 0; i < 9; ++i)
      hold[i] = move(this->cubies.at(face[i]));

    // Corners.
    this->cubies.at(face[6]) = move(hold.at(0));
    this->cubies.at(face[0]) = move(hold.at(2));
    this->cubies.at(face[8]) = move(hold.at(6));
    this->cubies.at(face[2]) = move(hold.at(8));

    // Edges.
    this->cubies.at(face[3]) = move(hold.at(1));
    this->cubies.at(face[7]) = move(hold.at(3));
    this->cubies.at(face[1]) = move(hold.at(5));
    this->cubies.at(face[5]) = move(hold.at(7));

    // Center.
    this->cubies.at(face[4]) = move(hold.at(4));
  }

  /**
   * See moveFace.  Move a slice. 
   * @param slice The slice to rotate clockwise.
   */
  void RubiksCube::moveSlice(const array<string, 8>& slice)
  {
    array<CubiePtr, 8> hold;

    // Copy all the cubie pointers.
    for (unsigned i = 0; i < 8; ++i)
      hold[i] = move(this->cubies.at(slice[i]));

    // Edges.
    this->cubies.at(slice[0]) = move(hold.at(6));
    this->cubies.at(slice[2]) = move(hold.at(0));
    this->cubies.at(slice[4]) = move(hold.at(2));
    this->cubies.at(slice[6]) = move(hold.at(4));

    // Centers.
    this->cubies.at(slice[1]) = move(hold.at(7));
    this->cubies.at(slice[3]) = move(hold.at(1));
    this->cubies.at(slice[5]) = move(hold.at(3));
    this->cubies.at(slice[7]) = move(hold.at(5));
  }

  /**
   * See moveFace.  Move a slice prime. 
   * @param slice The slice to rotate counter-clockwise.
   */
  void RubiksCube::moveSlicePrime(const array<string, 8>& slice)
  {
    array<CubiePtr, 8> hold;

    // Copy all the cubie pointers.
    for (unsigned i = 0; i < 8; ++i)
      hold[i] = move(this->cubies.at(slice[i]));

    // Edges.
    this->cubies.at(slice[0]) = move(hold.at(2));
    this->cubies.at(slice[2]) = move(hold.at(4));
    this->cubies.at(slice[4]) = move(hold.at(6));
    this->cubies.at(slice[6]) = move(hold.at(0));

    // Centers.
    this->cubies.at(slice[1]) = move(hold.at(3));
    this->cubies.at(slice[3]) = move(hold.at(5));
    this->cubies.at(slice[5]) = move(hold.at(7));
    this->cubies.at(slice[7]) = move(hold.at(1));
  }

  /**
   * Rotate the whole cube left.
   */
  void RubiksCube::rotateLeft()
  {
    this->u();
    this->dPrime();
    this->ePrime();
  }

  /**
   * Rotate the whole cube right.
   */
  void RubiksCube::rotateRight()
  {
    this->uPrime();
    this->d();
    this->e();
  }

  /**
   * Rotate the whole cube down.
   */
  void RubiksCube::rotateDown()
  {
    this->l();
    this->m();
    this->rPrime();
  }

  /**
   * Rotate the whole cube up.
   */
  void RubiksCube::rotateUp()
  {
    this->lPrime();
    this->mPrime();
    this->r();
  }

  /**
   * Rotate the UP face.
   */
  void RubiksCube::u()
  {
    float    rads = half_pi<float>();
    vec3     axis(0.0f, -1.0f, 0.0f);

    for (string face : this->faces["U"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["U"]);
  }

  /**
   * Rotate the UP face prime.
   */
  void RubiksCube::uPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, -1.0f, 0.0f);

    for (string face : this->faces["U"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["U"]);
  }

  /**
   * Rotate the UP face twice.
   */
  void RubiksCube::u2()
  {
    this->u();
    this->u();
  }

  /**
   * Rotate the LEFT face.
   */
  void RubiksCube::l()
  {
    float rads = half_pi<float>();
    vec3  axis(1.0f, 0.0f, 0.0f);

    for (string face : this->faces["L"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["L"]);
  }

  /**
   * Rotate the LEFT face prime.
   */
  void RubiksCube::lPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(1.0f, 0.0f, 0.0f);

    for (string face : this->faces["L"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["L"]);
  }

  /**
   * Rotate the LEFT face twice.
   */
  void RubiksCube::l2()
  {
    this->l();
    this->l();
  }

  /**
   * Rotate the FRONT face.
   */
  void RubiksCube::f()
  {
    float rads = half_pi<float>();
    vec3  axis(0.0f, 0.0f, -1.0f);

    for (string face : this->faces["F"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["F"]);
  }

  /**
   * Rotate the FRONT face prime.
   */
  void RubiksCube::fPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, 0.0f, -1.0f);

    for (string face : this->faces["F"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["F"]);
  }

  /**
   * Rotate the FRONT face twice.
   */
  void RubiksCube::f2()
  {
    this->f();
    this->f();
  }

  /**
   * Rotate the RIGHT face.
   */
  void RubiksCube::r()
  {
    float rads = half_pi<float>();
    vec3  axis(-1.0f, 0.0f, 0.0f);

    for (string face : this->faces["R"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["R"]);
  }

  /**
   * Rotate the RIGHT face prime.
   */
  void RubiksCube::rPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(-1.0f, 0.0f, 0.0f);

    for (string face : this->faces["R"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["R"]);
  }

  /**
   * Rotate the RIGHT face twice.
   */
  void RubiksCube::r2()
  {
    this->r();
    this->r();
  }

  /**
   * Rotate the BACK face.
   */
  void RubiksCube::b()
  {
    float rads = half_pi<float>();
    vec3  axis(0.0f, 0.0f, 1.0f);

    for (string face : this->faces["B"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["B"]);
  }

  /**
   * Rotate the BACK face prime.
   */
  void RubiksCube::bPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, 0.0f, 1.0f);

    for (string face : this->faces["B"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["B"]);
  }

  /**
   * Rotate the BACK face twice.
   */
  void RubiksCube::b2()
  {
    this->b();
    this->b();
  }

  /**
   * Rotate the DOWN face.
   */
  void RubiksCube::d()
  {
    float rads = half_pi<float>();
    vec3  axis(0.0f, 1.0f, 0.0f);

    for (string face : this->faces["D"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFace(this->faces["D"]);
  }

  /**
   * Rotate the DOWN face prime.
   */
  void RubiksCube::dPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, 1.0f, 0.0f);

    for (string face : this->faces["D"])
      this->cubies[face]->rotate(rads, axis);

    this->moveFacePrime(this->faces["D"]);
  }

  /**
   * Rotate the DOWN face twice.
   */
  void RubiksCube::d2()
  {
    this->d();
    this->d();
  }

  /**
   * Rotate the MIDDLE slice (between L and R, same way as L).
   */
  void RubiksCube::m()
  {
    float rads = half_pi<float>();
    vec3  axis(1.0f, 0.0f, 0.0f);

    for (string face : this->slices["M"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlice(this->slices["M"]);
  }

  /**
   * Rotate the MIDDLE slice prime (between L and R, same way as L).
   */
  void RubiksCube::mPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(1.0f, 0.0f, 0.0f);

    for (string face : this->slices["M"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlicePrime(this->slices["M"]);
  }

  /**
   * Rotate the MIDDLE slice twice (between L and R, same way as L).
   */
  void RubiksCube::m2()
  {
    return this->m();
    return this->m();
  }

  /**
   * Rotate the E slice (between U and D, same way as D).
   */
  void RubiksCube::e()
  {
    float rads = half_pi<float>();
    vec3  axis(0.0f, 1.0f, 0.0f);

    for (string face : this->slices["E"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlice(this->slices["E"]);
  }

  /**
   * Rotate the E slice prime (between U and D, same way as D).
   */
  void RubiksCube::ePrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, 1.0f, 0.0f);

    for (string face : this->slices["E"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlicePrime(this->slices["E"]);
  }

  /**
   * Rotate the E slice twice (between U and D, same way as D).
   */
  void RubiksCube::e2()
  {
    this->e();
    this->e();
  }

  /**
   * Rotate the S slice (between F and B, same way as F).
   */
  void RubiksCube::s()
  {
    float rads = half_pi<float>();
    vec3  axis(0.0f, 0.0f, -1.0f);

    for (string face : this->slices["S"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlice(this->slices["S"]);
  }

  /**
   * Rotate the S slice prime (between F and B, same way as F).
   */
  void RubiksCube::sPrime()
  {
    float rads = half_pi<float>() * -1;
    vec3  axis(0.0f, 0.0f, -1.0f);

    for (string face : this->slices["S"])
      this->cubies[face]->rotate(rads, axis);

    this->moveSlicePrime(this->slices["S"]);
  }

  /**
   * Rotate the S slice twice (between F and B, same way as F).
   */
  void RubiksCube::s2()
  {
    this->s2();
    this->s2();
  }
}

