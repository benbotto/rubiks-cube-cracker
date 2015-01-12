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
#include "rotate.h"
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
  inline void RubiksCubeModel3::roll90(FACE f)
  {
    /*
     * Usint arrays.
    unsigned base = ((unsigned)f) * 8;
    uint16_t hold = *((uint16_t*)&this->cube[base]);

    // Move two cubes at a time.  This halves the number of copies.
    *((uint16_t*)&this->cube[base])     = *((uint16_t*)&this->cube[base + 6]);
    *((uint16_t*)&this->cube[base + 6]) = *((uint16_t*)&this->cube[base + 4]);
    *((uint16_t*)&this->cube[base + 4]) = *((uint16_t*)&this->cube[base + 2]);
    *((uint16_t*)&this->cube[base + 2]) = hold;*/

    /*
     * Using pointers.
    uint16_t* const pFace = (uint16_t*)&this->cube[(unsigned)f * 8];
    uint16_t  hold  = *pFace;

    // Move two cubes at a time.  This halves the number of copies.
    *pFace       = *(pFace  + 6);
    *(pFace + 6) = *(pFace  + 4);
    *(pFace + 4) = *(pFace  + 2);
    *(pFace + 2) = hold;
    */
    

    /*
     * Using bit shifts.
    COLOR*    pFace = &this->cube[(unsigned)f * 8];
    uint16_t  hold  = *(uint16_t*)(pFace + 6);

    *(uint64_t*)pFace <<= 8;
    *(uint16_t*)pFace  = hold;
    */
    
   
    /* Bit shifts without pointers.
    unsigned base = ((unsigned)f) * 8;
    uint64_t face = *(uint64_t*)&this->cube[base];
    uint16_t hold = *(uint16_t*)&this->cube[base];

    //face <<= 8;
    *(uint64_t*)&this->cube[base] <<= 8;
    *((uint16_t*)&this->cube[base + 2]) = hold;
    */

    // roll with pointers.
    /*asm
    (
      "rolq %1, (%0)"
      :
      : "r" (&this->cube[(unsigned)f * 8]), "c" ((uint8_t)16)
    );*/

    
    uint64_t face = *(uint64_t*)&this->cube[(unsigned)f * 8];

    asm volatile 
    (
      "rolq %[by], %[face]"
      : [face] "+r" (face)
      : [by] "c" ((uint8_t)16)
    );

    *(uint64_t*)&this->cube[(unsigned)f * 8] = face;
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
    unsigned base = ((unsigned)f) * 8;
    uint32_t hold = *((uint32_t*)&this->cube[base]);

    // Move 4 cubes at a time.
    *((uint32_t*)&this->cube[base])     = *((uint32_t*)&this->cube[base + 4]);
    *((uint32_t*)&this->cube[base + 4]) = hold;
  }

  /**
   * Roll an array right 6 places, and wrap away.  This is a 270-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 2 3 4 5 6 7 0 1
   *
   * @param f The face to roll.
   */
  void RubiksCubeModel3::roll270(FACE f)
  {
    unsigned base = ((unsigned)f) * 8;
    uint16_t hold  = *((uint16_t*)&this->cube[base]);

    // Move 2 cubes at a time.
    *((uint16_t*)&this->cube[base])     = *((uint16_t*)&this->cube[base + 2]);
    *((uint16_t*)&this->cube[base + 2]) = *((uint16_t*)&this->cube[base + 4]);
    *((uint16_t*)&this->cube[base + 4]) = *((uint16_t*)&this->cube[base + 6]);
    *((uint16_t*)&this->cube[base + 6]) = hold;
  }

  /**
   * Rotate four sides as follows.
   * @param s_i0 The first index, treated as a short.
   * @param s_i1 The second index, treated as a short.
   * @param s_i2 The third index, treated as a short.
   * @param s_i3 The fourth index, treated as a short.
   * @param c_i0 The first index, treated as a char.
   * @param c_i1 The second index, treated as a char.
   * @param c_i2 The third index, treated as a char.
   * @param c_i3 The fourth index, treated as a char.
   */
  inline void RubiksCubeModel3::rotate90(unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
    unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3)
  {
    // The number of operations is reduced by moving two cubes at a time (e.g.
    // treating the cubes at index s_i0..s_i3 as 16-bit shorts).
    uint16_t hold_s_i0 = *((uint16_t*)&this->cube[s_i0]);

    *((uint16_t*)&this->cube[s_i0]) = *((uint16_t*)&this->cube[s_i1]);
    *((uint16_t*)&this->cube[s_i1]) = *((uint16_t*)&this->cube[s_i2]);
    *((uint16_t*)&this->cube[s_i2]) = *((uint16_t*)&this->cube[s_i3]);
    *((uint16_t*)&this->cube[s_i3]) = hold_s_i0;

    // The last four cubes need to be moved one at a time.
    COLOR hold_c_i0 = this->cube[c_i0];

    this->cube[c_i0] = this->cube[c_i1];
    this->cube[c_i1] = this->cube[c_i2];
    this->cube[c_i2] = this->cube[c_i3];
    this->cube[c_i3] = hold_c_i0;
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

    // Update the sides.
    this->rotate90(8, 16, 24, 32, 10, 18, 26, 34);

    return *this;
  }

  /**
   * Move the left face clockwise.
   */
  RubiksCubeModel3& RubiksCubeModel3::l()
  {
    this->roll90(FACE::LEFT);
    this->rotate90(6, 34, 46, 22, 0, 36, 40, 16);
    return *this;
  }

  /**
   * Move the front face clockwise.
   */
  RubiksCubeModel3& RubiksCubeModel3::f()
  {
    this->roll90(FACE::FRONT);
    this->rotate90(4, 10, 40, 30, 6, 12, 42, 24);
    return *this;
  }

  /**
   * Move the right face clockwise.
   */
  RubiksCubeModel3& RubiksCubeModel3::r()
  {
    this->roll90(FACE::RIGHT);
    this->rotate90(2, 18, 42, 38, 4, 20, 44, 32);
    return *this;
  }

  /**
   * Move the back face clockwise.
   */
  RubiksCubeModel3& RubiksCubeModel3::b()
  {
    this->roll90(FACE::BACK);
    this->rotate90(0, 26, 44, 14, 2, 28, 46, 8);
    return *this;
  }
}

