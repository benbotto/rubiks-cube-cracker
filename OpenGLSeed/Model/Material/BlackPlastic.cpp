#include "BlackPlastic.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  BlackPlastic::BlackPlastic() : Material(
    "BlackPlastic",
    vec4(0.0f, 0.0f, 0.0f, 1.0f),
    vec4(0.01f, 0.01f, 0.01f, 1.0f),
    vec4(0.5f, 0.5f, 0.5f, 1.0f),
    32.0f)
  {
  }
}

