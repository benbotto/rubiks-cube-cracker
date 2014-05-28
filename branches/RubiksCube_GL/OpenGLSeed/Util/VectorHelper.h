#include <glm/glm.hpp>
using glm::vec3;
using glm::abs;
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::fixed;

namespace busybin
{
  /**
   * Basic helper functions for vectors.
   */
  class VectorHelper
  {
  public:
    static void printVec(const glm::vec3& vec);
    static bool equal(const glm::vec3& v1, const glm::vec3& v2);
    static bool lessThan(const glm::vec3& v1, const glm::vec3& v2);
  };
}
