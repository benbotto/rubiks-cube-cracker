#include "Chrome.h"

namespace busybin
{
  /**
   * Initialize the Material.
   */
  Chrome::Chrome() : Material(
    "Chrome",
    glm::vec4(0.25f, 0.25f, 0.25f, 1.0f),
    glm::vec4(0.4f, 0.4f, 0.4f, 1.0f),
    /*glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f),*/
    glm::vec4(0.999f, 0.999f, 0.999f, 1.0f),
    /*76.8f*/ 200.0f)
    /*glm::vec4(0.999f, 0.999f, 0.999f, 1.0f),
    glm::vec4(0.999f, 0.999f, 0.999f, 1.0f),
    200.0f)*/
  {
  }
}

