#include "GrayPlastic.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  GrayPlastic::GrayPlastic() : Material(
    "GrayPlastic",
    vec4(0.01f, 0.01f, 0.01f, 1.0f),
    vec4(0.03f, 0.03f, 0.03f, 1.0f),
    vec4(0.1f, 0.1f, 0.1f, 1.0f),
    332.0f)
  {
  }
}

