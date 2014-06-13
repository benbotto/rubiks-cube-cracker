#include "RubiksCubeModel.h"

namespace busybin
{
  unsigned RubiksCubeModel::CubieHasher::operator()(const array<RubiksCubeModel::FACE, 2>& key) const
  {
    return ((unsigned)key[0] << 3) | (unsigned)key[1];
  }

  unsigned RubiksCubeModel::CubieHasher::operator()(const array<RubiksCubeModel::FACE, 3>& key) const
  {
    return ((unsigned)key[0] << 6) | ((unsigned)key[1] << 3) | (unsigned)key[2];
  }

  unsigned RubiksCubeModel::CubieHasher::operator()(
    const array<RubiksCubeModel::FACE, 2>& lhs,
    const array<RubiksCubeModel::FACE, 2>& rhs) const
  {
    for (unsigned i = 0; i < 2; ++i)
    {
      if (lhs[i] != rhs[i])
        return false;
    }
    
    return true;
  }

  unsigned RubiksCubeModel::CubieHasher::operator()(
    const array<RubiksCubeModel::FACE, 3>& lhs,
    const array<RubiksCubeModel::FACE, 3>& rhs) const
  {
    for (unsigned i = 0; i < 3; ++i)
    {
      if (lhs[i] != rhs[i])
        return false;
    }

    return true;
  }
}
