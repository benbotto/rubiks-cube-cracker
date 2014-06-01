#include "Pearl.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  Pearl::Pearl() : Material(
    "Pearl",
    glm::vec4(0.25f,     0.20725f,  0.20725f,  1.0f),
    glm::vec4(1.0f,      0.829f,    0.829f,    1.0f),
    glm::vec4(0.296648f, 0.296648f, 0.296648f, 1.0f),
    32.0f)
  {
  }
}

