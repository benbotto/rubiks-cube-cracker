#include "Gold.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  Gold::Gold() : Material(
    "Gold",
    glm::vec4(.2473f, .1995f, .0745f, 1.0f),
    glm::vec4(.7516f, .6065f, .2265f, 1.0f),
    glm::vec4(.6283f, .5559f, .3661f, 1.0f),
    51.20f)
  {
  }
}

