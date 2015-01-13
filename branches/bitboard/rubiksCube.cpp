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
  //RubiksCubeModel2 cube2;
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
  
  /*view3.render(cube3);
  cube3.u();
  view3.render(cube3);
  cube3.l();
  view3.render(cube3);
  cube3.r();
  view3.render(cube3);
  cube3.f();
  view3.render(cube3);
  cube3.b();
  view3.render(cube3);*/
  //cube3.u().r().l().b().l().u().f().rPrime().u().f().lPrime().b().l().b().r().l();
  //view3.render(cube3);
  //cube3.d2();
  //view3.render(cube3);
  /*view3.render(cube3);
  cube3.r();
  view3.render(cube3);
  cube3.b();
  view3.render(cube3);
  cube3.b();
  view3.render(cube3);
  cube3.d();
  view3.render(cube3);
  cube3.uPrime();
  view3.render(cube3);*/
  /*cube3.lPrime();
  view3.render(cube3);
  cube3.fPrime();
  view3.render(cube3);
  cube3.rPrime();
  view3.render(cube3);
  cube3.bPrime();
  view3.render(cube3);
  cube3.dPrime();
  view3.render(cube3);*/
  /*cube3.l().r().u().d();
  view3.render(cube3);
  cube3.m();
  view3.render(cube3);*/
  /*cube3.f().b().u().d().l().r();
  view3.render(cube3);
  cube3.e();
  view3.render(cube3);*/
  /*cube3.f().b().l().r();
  view3.render(cube3);
  cube3.s();
  view3.render(cube3);*/
  /*cube3.l().r().u().d();
  view3.render(cube3);
  cube3.mPrime();
  view3.render(cube3);*/
  /*cube3.f().b().u().d().l().r();
  view3.render(cube3);
  cube3.ePrime();
  view3.render(cube3);*/
  /*cube3.f().b().l().r();
  view3.render(cube3);
  cube3.sPrime();
  view3.render(cube3);*/
  /*cube3.l().r().u().d();
  view3.render(cube3);
  cube3.m2();
  view3.render(cube3);*/
  /*cube3.f().b().u().d().l().r();
  view3.render(cube3);
  cube3.e2();
  view3.render(cube3);*/
  /*cube3.f().b().l().r();
  view3.render(cube3);
  cube3.s2();
  view3.render(cube3);*/
  view3.render(cube3);
  cube3.zPrime();
  view3.render(cube3);
  
  /** Profiling. **/
  unsigned long nodes = pow(15, 8);

  {
    AutoTimer at;

    for (unsigned long i = 0; i < nodes; ++i)
      cube3.s2();
  }

  {
    AutoTimer at;

    for (unsigned long i = 0; i < nodes; ++i)
      cube.s2();
  }

  return 0;
}

