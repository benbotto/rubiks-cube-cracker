#include "RubiksCubeModel2.h" // TODO
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
  RubiksCubeModel2::RubiksCubeModel2() // TODO
  {
    // Each face is stored in a single long.  There are 6 sticker colors, so
    // each sticker can be stored in 3 bits.  A face is stored as follows,
    // bitwise.
    //
    //    0  3  6
    //   21     9
    //   18 15 12
    //
    // Rotating a face is therfore a simple shift left or right. (The center
    // cubies are not stored in the faces - they are stored in this->centers.)
    for (uchar i = 0; i < 6; ++i)
    {
      this->faces[i] = 0;

      for (int j = 0; j < 8; ++j)
      {
        this->faces[i] <<= 3;
        this->faces[i] |= i;
      }

      cout << "Face " << (unsigned)i << hex << " 0x" << this->faces[i]
           << " binary: " << (bitset<24>)this->faces[i] << endl;
    }

    // Store the center cubies.
    this->centers = ((uchar)COLOR::WHITE)        |
                    ((uchar)COLOR::GREEN  << 3)  |
                    ((uchar)COLOR::RED    << 6)  |
                    ((uchar)COLOR::BLUE   << 9)  |
                    ((uchar)COLOR::ORANGE << 12) |
                    ((uchar)COLOR::YELLOW << 15);

    // These masks are used to retrieve single sticker colors.
    for (int i = 0; i < 6; ++i) // TODO: not used.  If I use them, they are off right now.
    {
      for (int j = 0; j < 9; ++j)
        this->faceMasks[9 * i + j] = 7 << 3 * j;
    }

    // This is the amount that a sticker needs to be shifted right
    // to be stored in a COLOR (char).
    for (int i = 0; i < 6; ++i) // TODO: not used.  If I use them, they are off right now.
    {
      for (int j = 0; j < 9; ++j)
        this->faceShifts[9 * i + j] = 3 * j;
    }

    cout << endl;
    for (int i = 0; i < 9; ++i)
    {
      cout << "Mask " << i << hex << ": 0x" << setfill('0') << setw(7) << this->faceMasks[i]
           << " " << (bitset<32>)this->faceMasks[i] << endl;
    }

    cout << endl;
    for (int i = 0; i < 9; ++i)
    {
      cout << "Shift " << i << hex << ": 0x" << setfill('0') << setw(7) << this->faceShifts[i]
           << " " << (bitset<32>)this->faceShifts[i] << endl;
    }
    cout << endl;
  }

  /**
   * Roll an unsigned (a face) 90 degrees clockwise (e.g. shift all the bits
   * right 6 places and wrap the last two around, like ASM rol).
   * @param f The face to roll.
   */
  void RubiksCubeModel2::roll90(FACE f)
  {
    // Stickers 6 and 7, shifted to positions 0 and 1.
    unsigned lastTwo = (this->faces[(uchar)f] & 0xFC0000) >> 18;

    // Each sticker shifts over two places (6 bits), and the last two stickers,
    // 6 and 7, wrap around to positions 0 and 1.
    this->faces[(uchar)f] = (this->faces[(uchar)f] << 6) | lastTwo;
  }

  /**
   * Roll an unsigned (a face) 180 degrees clockwise.
   * @param f The face to roll.
   */
  void RubiksCubeModel2::roll180(FACE f)
  {
    // Stickers 6 and 7, shifted to positions 0 and 1.
    unsigned lastFour = (this->faces[(uchar)f] & 0xFFF000) >> 12;

    // Each sticker shifts over four places (12 bits), and the last four
    // stickers, 4, 5, 6 and 7, wrap around to positions 0, 1, 2, 3.
    this->faces[(uchar)f] = (this->faces[(uchar)f] << 12) | lastFour;
  }

  /**
   * Roll an unsigned (a face) 270 degrees clockwise.
   * @param f The face to roll.
   */
  void RubiksCubeModel2::roll270(FACE f)
  {
    // Stickers 6 and 7, shifted to positions 0 and 1.
    unsigned lastSix = (this->faces[(uchar)f] & 0xFFFFC0) >> 6;

    // Each sticker shifts over six places (18 bits), and the last six stickers
    // wrap around.
    this->faces[(uchar)f] = (this->faces[(uchar)f] << 18) | lastSix;
  }

  /**
   * Get one face of the cube, which is a bitmap of all the stickers on that
   * face.  Useful for debugging and printing.  The bounds are not checked.
   * @param f The face.
   */
  unsigned RubiksCubeModel2::getFace(FACE f) const
  {
    return this->faces[(unsigned)f];
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
   * Index wise:
   *
   *          0 1 2
   *          7   3
   *          6 5 4
   *
   *  0 1 2   0 1 2   0 1 2   0 1 2
   *  7   3   7   3   7   3   7   3
   *  6 5 4   6 5 4   6 5 4   6 5 4
   *
   *          0 1 2
   *          7   3
   *          6 5 4
   *
   * @param i The index.
   */
  /*RubiksCubeModel2::COLOR RubiksCubeModel2::get(unsigned i) const
  {
    unsigned mask  = this->faceMasks[i];
    unsigned shift = this->faceShifts[i];

    return (COLOR)((this->faces[i / 9] & mask) >> shift);
  }*/

  /**
   * Get the color at FACE, row, col.  See get(i) overload for doc.
   * @param f The face of the cube.
   * @param row The 0-based row, unfolded as described in get(i).
   * @param col The 0-based col, unfulded as described in get(i).
   */
  RubiksCubeModel2::COLOR RubiksCubeModel2::get(
    FACE f, unsigned row, unsigned col) const
  {
    if (row == 1 and col == 1)
    {
      // Center piece.
      unsigned shift = (unsigned)f * 3;
      unsigned mask  = 7 << shift;

      return (COLOR)((this->centers & mask) >> shift);
    }
    else
    {
      // A face stores stickers as follows.
      // 0 1 2
      // 7   3
      // 6 5 4

      unsigned  lookup[] = {0, 1, 2, 7, 0, 3, 6, 5, 4};
      unsigned  index    = lookup[row * 3 + col];
      unsigned  shift    = index * 3;
      unsigned  mask     = 7 << shift;

      return (COLOR)((this->faces[(unsigned)f] & mask) >> shift);
    }
  }

  /**
   * Move the up face clockwise.
   */
  RubiksCubeModel2& RubiksCubeModel2::u()
  {
    // Stickers 6 and 7, shifted to positions 0 and 1.
    //unsigned lastTwo = (this->faces[(uchar)FACE::UP] & 0xFC0000) >> 18;

    unsigned sideMask = 0x1FF;     // Stickers 0, 1, and 2 on a face.
    unsigned flipped  = 0xFFFE00;  // ~sideMask.

    // Stickers 0, 1, and 2 from the sides.
    unsigned front3 = this->faces[(uchar)FACE::FRONT] & sideMask;
    unsigned right3 = this->faces[(uchar)FACE::RIGHT] & sideMask;
    unsigned back3  = this->faces[(uchar)FACE::BACK]  & sideMask;
    unsigned left3  = this->faces[(uchar)FACE::LEFT]  & sideMask;

    // Rotate each sticker 90 degrees on the face.
    this->roll90(FACE::UP);

    // Each sticker shifts over two places (6 bits), and the last two stickers
    // - 6 and 7 - wrap around to positions 0 and 1.
    //this->faces[(uchar)FACE::UP] = (this->faces[(uchar)FACE::UP] << 6) | lastTwo;

    // Zero out the bits corresponding to stickers 0, 1, and 2.
    this->faces[(uchar)FACE::LEFT]  &= flipped;
    this->faces[(uchar)FACE::FRONT] &= flipped;
    this->faces[(uchar)FACE::RIGHT] &= flipped;
    this->faces[(uchar)FACE::BACK]  &= flipped;

    // Rotate the sides.
    this->faces[(uchar)FACE::LEFT]  |= front3;
    this->faces[(uchar)FACE::FRONT] |= right3;
    this->faces[(uchar)FACE::RIGHT] |= back3;
    this->faces[(uchar)FACE::BACK]  |= left3;

    return *this;
  }

  /**
   * Move the left face clockwise.
   */
  RubiksCubeModel2& RubiksCubeModel2::l()
  {
    unsigned sideMask  = 0xFC0007;  // Stickers 0, 6, and 7 on a face.
    unsigned flipped   = 0x3FFF8;   // ~sideMask.
    
    // The back needs to be rolled 180 degrees so that stickers 0, 6 and 7
    // replace stickers 2, 3, and 4.
    this->roll180(FACE::BACK);

    // Stickers 0, 6, and 7 from the sides.
    unsigned up3    = this->faces[(uchar)FACE::UP]    & sideMask;
    unsigned front3 = this->faces[(uchar)FACE::FRONT] & sideMask;
    unsigned down3  = this->faces[(uchar)FACE::DOWN]  & sideMask;
    unsigned back3  = this->faces[(uchar)FACE::BACK]  & sideMask;

    // Rotate each sticker 90 degrees on the face.
    this->roll90(FACE::LEFT);

    // Zero out the bits corresponding to stickers 0, 6, and 7.
    this->faces[(uchar)FACE::UP]    &= flipped;
    this->faces[(uchar)FACE::FRONT] &= flipped;
    this->faces[(uchar)FACE::DOWN]  &= flipped;
    this->faces[(uchar)FACE::BACK]  &= flipped;

    // Rotate the sides.
    this->faces[(uchar)FACE::UP]    |= back3;
    this->faces[(uchar)FACE::BACK]  |= down3;
    this->faces[(uchar)FACE::DOWN]  |= front3;
    this->faces[(uchar)FACE::FRONT] |= up3;

    // Restore the back.
    this->roll180(FACE::BACK);

    return *this;
  }

  /**
   * Move the front face clockwise.
   */
  RubiksCubeModel2& RubiksCubeModel2::f()
  {
    unsigned sideMask  = 0xFC0007;  // Stickers 0, 6, and 7 on a face.
    unsigned flipped   = 0x3FFF8;   // ~sideMask.
    
    this->roll180(FACE::LEFT);
    this->roll270(FACE::UP);
    this->roll90(FACE::DOWN);

    // Stickers 0, 6, and 7 from the sides.
    unsigned up3    = this->faces[(uchar)FACE::UP]    & sideMask;
    unsigned right3 = this->faces[(uchar)FACE::RIGHT] & sideMask;
    unsigned down3  = this->faces[(uchar)FACE::DOWN]  & sideMask;
    unsigned left3  = this->faces[(uchar)FACE::LEFT]  & sideMask;

    // Rotate each sticker 90 degrees on the face.
    this->roll90(FACE::LEFT);

    // Zero out the bits corresponding to stickers 0, 6, and 7.
    this->faces[(uchar)FACE::UP]    &= flipped;
    this->faces[(uchar)FACE::RIGHT] &= flipped;
    this->faces[(uchar)FACE::DOWN]  &= flipped;
    this->faces[(uchar)FACE::LEFT]  &= flipped;

    // Rotate the sides.
    this->faces[(uchar)FACE::UP]    |= left3;
    this->faces[(uchar)FACE::LEFT]  |= down3;
    this->faces[(uchar)FACE::DOWN]  |= right3;
    this->faces[(uchar)FACE::RIGHT] |= up3;

    this->roll180(FACE::LEFT);
    this->roll90(FACE::UP);
    this->roll270(FACE::DOWN);

    return *this;
  }
}

