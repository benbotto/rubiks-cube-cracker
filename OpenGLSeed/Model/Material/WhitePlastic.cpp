#include "WhitePlastic.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  WhitePlastic::WhitePlastic() : Material(
    "WhitePlastic",
    vec4(0.33f, 0.33f, 0.33f, 1.0f),
    vec4(0.88f, 0.88f, 0.88f, 1.0f),
    vec4(0.7f, 0.7f, 0.7f, 1.0f),
    32.0f)
  {
  }
}

