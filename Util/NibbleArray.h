#ifndef _BUSYBIN_NIBBLE_ARRAY_
#define _BUSYBIN_NIBBLE_ARRAY_

#include <cstddef>
using std::size_t;
#include <array>
using std::array;

namespace busybin
{
  /**
   * This class is an array, but stores each element in 4 bits (a nibble).
   */
  template <size_t SIZE>
  class NibbleArray
  {
    typedef unsigned char uchar;

    array<uchar, SIZE / 2> arr;
  public:
    /**
     * Initialize the underlying array to all 0s.
     */
    NibbleArray() : arr{{0}}
    {
    }

    /**
     * Access the element at index pos.
     * @param pos The 0-based index of the element.
     */
    uchar get(const size_t pos) const
    {
      size_t i = pos / 2;
      uchar val = this->arr.at(i);

      if (pos % 2)
      {
        // Odd: last 4 bits.
        return val & 0x0F;
      }
      else
      {
        // Even: first 4 bits.
        return val >> 4;
      }
    }

    /**
     * Set the element at index pos.
     * @param pos The 0-based index of the element.
     * @param val The value to set, which can be at most 15 (other bits will be
     * zeroed).
     */
    void set(const size_t pos, uchar val)
    {
      size_t i = pos / 2;
      uchar curVal = this->arr.at(i);

      if (pos % 2)
      {
        // Odd: last 4 bits.
        this->arr.at(i) = (curVal & 0xF0) | (val & 0x0F);
      }
      else
      {
        // Even: first 4 bits.
        this->arr.at(i) = (val << 4) | (curVal & 0x0F);
      }
    }
  };
}

#endif
