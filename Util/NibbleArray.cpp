#include "NibbleArray.h"

namespace busybin
{
  /**
   * Initialize the underlying vector.
   */
  NibbleArray::NibbleArray(const size_t size, const uchar val) : arr(size / 2 + 1, val)
  {
  }

  /**
   * Access the element at index pos.
   * @param pos The 0-based index of the element.
   */
  unsigned char NibbleArray::get(const size_t pos) const
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
  void NibbleArray::set(const size_t pos, const uchar val)
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

  /**
   * Get a pointer to the underlying array.
   */
  unsigned char* NibbleArray::data()
  {
    return this->arr.data();
  }

  /**
   * Get a pointer to the underlying array.
   */
  const unsigned char* NibbleArray::data() const
  {
    return this->arr.data();
  }

  /**
   * Get the size of the data in the underlying array.
   */
  size_t NibbleArray::storageSize() const
  {
    return this->arr.size();
  }
}

