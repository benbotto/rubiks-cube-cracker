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
   * @param pWorldWnd The world window, used to get the current width/heigth.
   * @param pCube Pointer to the RubiksCubeModel.
   * @param pView Pointer to the RubiksViewModel.
   */
  CubeDumper::CubeDumper(World* pWorld, WorldWindow* pWorldWnd) : 
    Command(pWorld, pWorldWnd)
  {
    // Listen for keypress events.
    pWorldWnd->onKeypress(bind(&CubeDumper::onKeypress, ref(*this), _1, _2, _3, _4));

    this->pCube = dynamic_cast<RubiksCube*>(&pWorld->at("RubiksCube"));
  }

  /**
   * Fires when a key is pressed
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeDumper::onKeypress(int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_SPACE)
      this->view.render(this->pCube->getRawModel());
  }
}

