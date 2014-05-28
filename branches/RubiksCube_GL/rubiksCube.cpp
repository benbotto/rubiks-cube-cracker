#include "Controller/RubiksCubeController.h"

/**
 * Bootstrap the application.
 */
int main(int argc, char* argv[])
{
  busybin::RubiksCubeController ctlr;
  ctlr.run();
  return 0;
}

