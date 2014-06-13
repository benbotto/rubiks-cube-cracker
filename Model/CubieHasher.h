#ifndef _BUSYBIN_CUBIE_HASHER_H_
#define _BUSYBIN_CUBIE_HASHER_H_

#include <cstddef>
using std::size_t;
#include <array>
using std::array;

namespace busybin
{
  /*class RubiksCubeModel
  {
  public:
    enum class FACE : unsigned char;
  };*/

  template <size_t N>
  class CubieHasher
  {
  public:
    unsigned operator()(const array<unsigned char, N>& key) const
    {
      unsigned hash = 0;

      for (unsigned i = 0; i < N; ++i)
        hash = (hash << 8) | key[i];

      return hash;
    }
  };

  template <size_t N>
  class CubieComp
  {
  public:
    unsigned operator()(const array<unsigned char, N>& lhs, const array<unsigned char, N>& rhs) const
    {
      for (unsigned i = 0; i < N; ++i)
      {
        if (lhs[i] != rhs[i])
          return false;
      }
      return true;
    }
  };
}

#endif

