#include "GrayPlastic.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  GrayPlastic::GrayPlastic() : Material(
    "GrayPlastic",
    vec4(0.01f, 0.01f, 0.01f, 1.0f),
    vec4(0.15f, 0.15f, 0.15f, 1.0f),
    vec4(0.5f, 0.5f, 0.5f, 1.0f),
    332.0f)
  {
  }
}

