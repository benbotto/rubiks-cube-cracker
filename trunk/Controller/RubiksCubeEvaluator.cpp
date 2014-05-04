#include "RubiksCubeEvaluator.h"

#include <iostream> // TODO: remove
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Init.
   */
  RubiksCubeEvaluator::RubiksCubeEvaluator()
  {
  }

  /**
   * Evaluate the cube.  10 points are awarded for each solved cubie.
   * @param cube The RubiksCube.
   */
  unsigned RubiksCubeEvaluator::eval(const RubiksCube& cube) const
  {
    unsigned score = 0;
    RubiksCube::COLOR upColor    = cube.get(RubiksCube::FACE::UP,    1, 1);
    RubiksCube::COLOR downColor  = cube.get(RubiksCube::FACE::DOWN,  1, 1);
    RubiksCube::COLOR leftColor  = cube.get(RubiksCube::FACE::LEFT,  1, 1);
    RubiksCube::COLOR rightColor = cube.get(RubiksCube::FACE::RIGHT, 1, 1);
    RubiksCube::COLOR frontColor = cube.get(RubiksCube::FACE::FRONT, 1, 1);
    RubiksCube::COLOR backColor  = cube.get(RubiksCube::FACE::BACK,  1, 1);

    /******
     * UP.
     ******/

    // Corner: up, back, left.
    if (cube.get(RubiksCube::FACE::UP,   0, 0) == upColor   &&
        cube.get(RubiksCube::FACE::BACK, 0, 2) == backColor &&
        cube.get(RubiksCube::FACE::LEFT, 0, 0) == leftColor)
    {
      score += 5;
      cout << "up, back, left solved." << endl;
    }

    // Edge: up, back.
    if (cube.get(RubiksCube::FACE::UP,   0, 1) == upColor   &&
        cube.get(RubiksCube::FACE::BACK, 0, 1) == backColor)
    {
      score += 5;
      cout << "up, back solved." << endl;
    }

    // Corner: up, back, right.
    if (cube.get(RubiksCube::FACE::UP,    0, 2) == upColor   &&
        cube.get(RubiksCube::FACE::BACK,  0, 0) == backColor &&
        cube.get(RubiksCube::FACE::RIGHT, 0, 2) == rightColor)
    {
      score += 5;
      cout << "up, back, right solved." << endl;
    }

    // Edge: up, left.
    if (cube.get(RubiksCube::FACE::UP,   1, 0) == upColor   &&
        cube.get(RubiksCube::FACE::LEFT, 0, 1) == leftColor)
    {
      score += 5;
      cout << "up, left solved." << endl;
    }

    // Edge: up, right.
    if (cube.get(RubiksCube::FACE::UP,    1, 2) == upColor   &&
        cube.get(RubiksCube::FACE::RIGHT, 0, 1) == rightColor)
    {
      score += 5;
      cout << "up, right solved." << endl;
    }

    // Corner: up, front, left.
    if (cube.get(RubiksCube::FACE::UP,    2, 0) == upColor    &&
        cube.get(RubiksCube::FACE::FRONT, 0, 0) == frontColor &&
        cube.get(RubiksCube::FACE::LEFT,  0, 2) == leftColor)
    {
      score += 5;
      cout << "up, front, left solved." << endl;
    }

    // Edge: up, front.
    if (cube.get(RubiksCube::FACE::UP,    2, 1) == upColor    &&
        cube.get(RubiksCube::FACE::FRONT, 0, 1) == frontColor)
    {
      score += 5;
      cout << "up, front solved." << endl;
    }

    // Corner: up, front, right.
    if (cube.get(RubiksCube::FACE::UP,    2, 2) == upColor    &&
        cube.get(RubiksCube::FACE::FRONT, 0, 2) == frontColor &&
        cube.get(RubiksCube::FACE::RIGHT, 0, 0) == rightColor)
    {
      score += 5;
      cout << "up, front, right solved." << endl;
    }

    /*********
     * MIDDLE.
     *********/

    // Edge: front, left.
    if (cube.get(RubiksCube::FACE::FRONT, 1, 0) == frontColor &&
        cube.get(RubiksCube::FACE::LEFT,  1, 2) == leftColor)
    {
      score += 5;
      cout << "front, left solved." << endl;
    }

    // Edge: front, right.
    if (cube.get(RubiksCube::FACE::FRONT, 1, 2) == frontColor &&
        cube.get(RubiksCube::FACE::RIGHT, 1, 0) == rightColor)
    {
      score += 5;
      cout << "front, right solved." << endl;
    }

    // Edge: left, back.
    if (cube.get(RubiksCube::FACE::LEFT, 1, 0) == leftColor &&
        cube.get(RubiksCube::FACE::BACK, 1, 2) == backColor)
    {
      score += 5;
      cout << "left, back solved." << endl;
    }

    // Edge: right, back.
    if (cube.get(RubiksCube::FACE::RIGHT, 1, 2) == rightColor &&
        cube.get(RubiksCube::FACE::BACK,  1, 0) == backColor)
    {
      score += 5;
      cout << "right, back solved." << endl;
    }

    /********
     * DOWN.
     ********/

    // Corner: down, front, left.
    if (cube.get(RubiksCube::FACE::DOWN,  0, 0) == downColor   &&
        cube.get(RubiksCube::FACE::FRONT, 2, 0) == frontColor &&
        cube.get(RubiksCube::FACE::LEFT,  2, 2) == leftColor)
    {
      score += 5;
      cout << "down, front, left solved." << endl;
    }

    // Edge: down, front.
    if (cube.get(RubiksCube::FACE::DOWN,  0, 1) == downColor &&
        cube.get(RubiksCube::FACE::FRONT, 2, 1) == frontColor)
    {
      score += 5;
      cout << "down, front solved." << endl;
    }

    // Corner: down, front, right.
    if (cube.get(RubiksCube::FACE::DOWN,  0, 2) == downColor   &&
        cube.get(RubiksCube::FACE::FRONT, 2, 2) == frontColor &&
        cube.get(RubiksCube::FACE::RIGHT, 2, 0) == rightColor)
    {
      score += 5;
      cout << "down, front, right solved." << endl;
    }

    // Edge: down, left.
    if (cube.get(RubiksCube::FACE::DOWN, 1, 0) == downColor &&
        cube.get(RubiksCube::FACE::LEFT, 2, 1) == leftColor)
    {
      score += 5;
      cout << "down, left solved." << endl;
    }

    // Edge: down, right.
    if (cube.get(RubiksCube::FACE::DOWN,  1, 2) == downColor &&
        cube.get(RubiksCube::FACE::RIGHT, 2, 1) == rightColor)
    {
      score += 5;
      cout << "down, right solved." << endl;
    }

    // Corner: down, back, left.
    if (cube.get(RubiksCube::FACE::DOWN, 2, 0) == downColor &&
        cube.get(RubiksCube::FACE::BACK, 2, 2) == backColor &&
        cube.get(RubiksCube::FACE::LEFT, 2, 0) == leftColor)
    {
      score += 5;
      cout << "down, back, left solved." << endl;
    }
    
    // Edge: down, back.
    if (cube.get(RubiksCube::FACE::DOWN, 2, 1) == downColor &&
        cube.get(RubiksCube::FACE::BACK, 2, 1) == backColor)
    {
      score += 5;
      cout << "down, back solved." << endl;
    }

    // Corner: down, back, right.
    if (cube.get(RubiksCube::FACE::DOWN,  2, 2) == downColor &&
        cube.get(RubiksCube::FACE::BACK,  2, 0) == backColor &&
        cube.get(RubiksCube::FACE::RIGHT, 2, 2) == rightColor)
    {
      score += 5;
      cout << "down, back, right solved." << endl;
    }

    return score;
  }
}

