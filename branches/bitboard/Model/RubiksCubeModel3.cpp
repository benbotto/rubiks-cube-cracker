#include "RubiksCubeModel3.h" // TODO
// TODO
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::hex;
using std::setfill;
using std::setw;
#include <bitset>
using std::bitset;
// END TODO

namespace busybin
{
  /**
   * Initialize the cube, white on top, red in front.
   */
  RubiksCubeModel3::RubiksCubeModel3() // TODO
  {
    array<COLOR, 48>::iterator it  = this->cube.begin();
    array<COLOR, 48>::iterator end = next(it, 8);

    // Top.
    fill(it, end, COLOR::WHITE);

    // Left.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::GREEN);

    // Front.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::RED);

    // Right.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::BLUE);

    // Back.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::ORANGE);

    // Bottom.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::YELLOW);

    // The center cubes are stored separately.  This allows for very fast
    // face rotations.  Additionally this allows each face to fit in
    // 64 bits, which can speed up solution checks.
    for (int i = 0; i < 6; ++i)
      this->centers[i] = (COLOR)i;
  }

  /**
   * Get the color at index i.  The cube is laid out as follows.
   * The index i is not checked (for speed).  Make sure i < 54!
   *
   *          W W W
   *          W W W
   *          W W W
   *
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *
   *          Y Y Y
   *          Y Y Y
   *          Y Y Y
   *
   * The sides:
   *
   *     U
   *   L F R B
   *     D
   *
   * Index wise:
   *
   *
   *              0  1  2
   *              7     3
   *              6  5  4
   *
   *   8  9 10   16 17 18   24 25 26   32 33 34
   *  15    11   23    19   31    27   39    35
   *  14 13 12   22 21 20   30 29 28   38 37 36
   *
   *             40 41 42
   *             47    43
   *             46 45 44
   *
   * @param i The index.
   */
  /*RubiksCubeModel3::COLOR RubiksCubeModel3::get(unsigned i) const
  {
    unsigned mask  = this->faceMasks[i];
    unsigned shift = this->faceShifts[i];

    return (COLOR)((this->faces[i / 9] & mask) >> shift);
  }*/

  /**
   * Roll an array right 2 places, and wrap around.  This is a 90-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 6 7 0 1 2 3 4 5 
   *
   * @param f The face to roll.
   */
  void RubiksCubeModel3::roll90(FACE f)
  {
    uint16_t hold = *((uint16_t*)&this->cube[0]);

    // Move two cubes at a time.  This halves the number of copies.
    *((uint16_t*)&this->cube[0]) = *((uint16_t*)&this->cube[6]);
    *((uint16_t*)&this->cube[6]) = *((uint16_t*)&this->cube[4]);
    *((uint16_t*)&this->cube[4]) = *((uint16_t*)&this->cube[2]);
    *((uint16_t*)&this->cube[2]) = hold;
  }

  /**
   * Roll an array right 4 places, and wrap away.  This is a 180-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 4 5 6 7 0 1 2 3 
   *
   * @param f The face to roll.
   */
  void RubiksCubeModel3::roll180(FACE f)
  {
    uint32_t hold = *((uint32_t*)&this->cube[0]);

    // Move 4 cubes at a time.
    *((uint32_t*)&this->cube[0]) = *((uint32_t*)&this->cube[4]);
    *((uint32_t*)&this->cube[4]) = hold;
  }

  /**
   * Roll an array right 6 places, and wrap away.  This is a 270-degree
   * rotation of a face.
   *
   * 0 1 2 3 4 5 6 7 
   * 2 3 4 5 6 7 0 1
   *
   * @param f The face to roll.
   */
  void RubiksCubeModel3::roll270(FACE f)
  {
    uint16_t hold = *((uint16_t*)&this->cube[0]);

    // Move 2 cubes at a time.
    *((uint16_t*)&this->cube[0]) = *((uint16_t*)&this->cube[2]);
    *((uint16_t*)&this->cube[2]) = *((uint16_t*)&this->cube[4]);
    *((uint16_t*)&this->cube[4]) = *((uint16_t*)&this->cube[6]);
    *((uint16_t*)&this->cube[6]) = hold;
  }

  /**
   * Get the color at FACE, row, col.
   * @param f The face of the cube.
   * @param row The 0-based row, unfolded as described in get(i).
   * @param col The 0-based col, unfulded as described in get(i).
   */
  RubiksCubeModel3::COLOR RubiksCubeModel3::get(
    FACE f, unsigned row, unsigned col) const
  {
    if (row == 1 and col == 1)
      return (COLOR)this->centers[(unsigned)f];
    else
    {
      /* Row-column lookup.  A face stores stickers as follows.
       *  
       *  0 1 2
       *  7   3
       *  6 5 4
       *
       *  So, for example, row 2 col 1 is at index 5.
       *  row * 3 + col = 2 * 3 + 1 = 7.  lookup[7] == 5.
       */
      unsigned lookup[] = {0, 1, 2, 7, 0, 3, 6, 5, 4};
      unsigned index    = lookup[row * 3 + col];

      return (COLOR)this->cube[(unsigned)f * 8 + index];
    }
  }

  /**
   * Move the up face clockwise.
   */
  RubiksCubeModel3& RubiksCubeModel3::u()
  {
    // Rotate the stickers on the face.
    this->roll90(FACE::UP);

    //Update the sides.
    uint16_t hold_8_9 = *((uint16_t*)&this->cube[8]);
    COLOR    hold_10  = this->cube[10];

    *((uint16_t*)&this->cube[8])  = *((uint16_t*)&this->cube[16]);
    this->cube[10]                = this->cube[18];
    *((uint16_t*)&this->cube[16]) = *((uint16_t*)&this->cube[24]);
    this->cube[18]                = this->cube[26];
    *((uint16_t*)&this->cube[24]) = *((uint16_t*)&this->cube[32]);
    this->cube[26]                = this->cube[34];
    *((uint16_t*)&this->cube[32]) = hold_8_9;
    this->cube[34]                = hold_10;

    return *this;
  }
}

