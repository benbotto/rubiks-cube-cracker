#include "Controller/RubiksCubeController.h"

int main(int argc, char* argv[])
{
  busybin::RubiksCubeController ctlr;

  ctlr.start();

  return 0;
}

