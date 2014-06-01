#include "Brass.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  Brass::Brass() : Material(
    "Brass",
    glm::vec4(.3294f, .2235f, .02745f, 1.0f),
    glm::vec4(.7804f, .5686f, .1137f,  1.0f),
    glm::vec4(.9922f, .9412f, .8078f,  1.0f),
    27.9f)
  {
  }
}

