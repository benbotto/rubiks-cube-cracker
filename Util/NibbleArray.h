#ifndef _BUSYBIN_NIBBLE_ARRAY_
#define _BUSYBIN_NIBBLE_ARRAY_

#include <cstddef>
using std::size_t;
#include <vector>
using std::vector;
#include <cstdint>
#include <algorithm>
using std::fill;

namespace busybin
{
  /**
   * This class is an array, but stores each element in 4 bits (a nibble).
   */
  class NibbleArray
  {
    size_t size;

    // This is where the data are stored.  It's a vector rather than an array
    // because the OS imposes stack size limitations, and very large arrays are
    // needed to hold the pattern databases.
    vector<uint8_t> arr;

  public:
    NibbleArray(const size_t size, const uint8_t val = 0xFF);
    uint8_t get(const size_t pos) const;
    void set(const size_t pos, const uint8_t val);
    unsigned char* data();
    const unsigned char* data() const;
    size_t storageSize() const;
    void inflate(vector<uint8_t>& dest) const;
    void reset(const uint8_t val = 0xFF);
  };
}

#endif
