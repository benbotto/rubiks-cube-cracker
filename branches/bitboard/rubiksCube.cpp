#include "Controller/RubiksCubeController.h"

// TODO
#include "Model/RubiksCubeModel3.h"
#include "Model/RubiksCubeModel2.h"
#include "Model/RubiksCubeModel.h"
#include "View/RubiksCubeView2.h"
#include "View/RubiksCubeView3.h"
#include "Util/AutoTimer.h"
#include <cmath>
using namespace busybin;
// END TODO

/**
 * Bootstrap the application.
 */
int main(int argc, char* argv[])
{
  /*busybin::RubiksCubeController ctlr;
  ctlr.run();*/

  RubiksCubeModel cube;
  RubiksCubeModel2 cube2;
  RubiksCubeModel3 cube3;
  //RubiksCubeView2 view2;
  RubiksCubeView3 view3;

  //view2.renderRaw(cube2);
  //view2.render(cube2);

  //cube2.u().l().u().l();
  //cube2.l().l();
  //cube2.u();
  //cube2.l().u();
  //cube2.u().l();
  //cube2.f();

  //view2.render(cube2);
  
  view3.render(cube3);
  cube3.u();
  view3.render(cube3);
  
  /** Profiling. **/
  unsigned long nodes = pow(15, 8);

  {
    AutoTimer at;

    for (unsigned long i = 0; i < nodes; ++i)
      cube3.u();
  }

  /*{
    AutoTimer at;

    for (unsigned long i = 0; i < nodes; ++i)
      cube2.f();
  }*/

  {
    AutoTimer at;

    for (unsigned long i = 0; i < nodes; ++i)
      cube.u();
  }

  return 0;
}

