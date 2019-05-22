#include "CubeDumper.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

namespace busybin
{
  /**
   * Init - store references to the cube and view.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, for binding keypress events.
   */
  CubeDumper::CubeDumper(World* pWorld, WorldWindow* pWorldWnd) : 
    Command(pWorld, pWorldWnd)
  {
    // Listen for keypress events.
    pWorldWnd->onKeypress(bind(&CubeDumper::onKeypress, ref(*this), _1, _2, _3, _4));

    this->pCube = dynamic_cast<RubiksCubeWorldObject*>(&pWorld->at("RubiksCube"));
  }

  /**
   * Fires when a key is pressed and dumps the cube to the console.
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeDumper::onKeypress(int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
      this->view.render(this->pCube->getRawModel());
  }
}

