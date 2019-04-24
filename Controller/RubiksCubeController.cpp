#include "RubiksCubeController.h"

namespace busybin
{
  /**
   * Main controller.  Sets up the Word, Views, and commands.
   */
  void RubiksCubeController::run()
  {
    try
    {
      // Pass width and height for windowed-mode.
      WorldWindow              worldWnd("Rubik's Cube", 1024, 768);
      RubiksCubeWorld          world(unique_ptr<Program>(new RubiksCubeProgram()));
      ViewManager              viewMan(&world,    &worldWnd);
      Renderer                 renderer(&world,   &worldWnd);
      CubeMover                cubeMover(&world,  &worldWnd);
      ThreadPool               threadPool(1);
      ThistlethwaiteCubeSolver tCubeSolver(&world, &worldWnd, &cubeMover, &threadPool);
      KorfCubeSolver           kCubeSolver(&world, &worldWnd, &cubeMover, &threadPool);
      CubeDumper               cubeDumper(&world, &worldWnd);

      tCubeSolver.initialize();
      kCubeSolver.initialize();

      // All wired up, run the main loop.
      worldWnd.run();
    }
    catch (const exception& ex)
    {
      cout << "Exception encountered.\n" << ex.what() << endl;
    }
  }
}

