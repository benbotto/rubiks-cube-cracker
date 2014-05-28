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
      WorldWindow     worldWnd("OpenGL Seed");
      RubiksCubeWorld world(unique_ptr<Program>(new RubiksCubeProgram()));
      ViewManager     viewMan(&world, &worldWnd);
      Mover           Mover(&world, &worldWnd);
      Looker          Looker(&world, &worldWnd);
      Renderer        renderer(&world, &worldWnd);

      // All wired up, run the main loop.
      worldWnd.run();
    }
    catch (const exception& ex)
    {
      cout << "Exception encountered." << endl;
      cout << ex.what() << endl;
    }
  }
}

