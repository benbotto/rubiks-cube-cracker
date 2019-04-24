#ifndef _BUSYBIN_NIBBLE_ARRAY_
#define _BUSYBIN_NIBBLE_ARRAY_

#include <cstddef>
using std::size_t;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * This class is an array, but stores each element in 4 bits (a nibble).
   */
  class NibbleArray
  {
    typedef unsigned char uchar;

    // This is where the data are stored.  It's a vector rather than an array
    // because the OS imposes stack size limitations, and very large arrays are
    // needed to hold the pattern databases.
    vector<uchar> arr;
  public:
    NibbleArray(const size_t size, const uchar val = 0xFF);
    uchar get(const size_t pos) const;
    void set(const size_t pos, const uchar val);
    unsigned char* data();
    const unsigned char* data() const;
    size_t storageSize() const;
  };
}

#endif
