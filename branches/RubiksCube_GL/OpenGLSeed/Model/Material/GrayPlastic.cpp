#include "GrayPlastic.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  GrayPlastic::GrayPlastic() : Material(
    "GrayPlastic",
    vec4(0.01f, 0.01f, 0.01f, 1.0f),
    vec4(0.05f, 0.05f, 0.05f, 1.0f),
    vec4(0.2f, 0.2f, 0.2f, 1.0f),
    32.0f)
  {
  }
}

