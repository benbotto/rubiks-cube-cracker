#ifndef _BUSYBIN_WORLD_WINDOW_H_
#define _BUSYBIN_WORLD_WINDOW_H_

#define GLM_FORCE_RADIANS

#include "../Util/GLException.h"
#include <GL/glew.h> // Note: must be included before glfw3.h.
#include <GLFW/glfw3.h>
#include <string>
using std::string;
#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;

namespace busybin
{
  /**
   * Bassic OpenGL window (C++ wrapper for GLFW).
   */
  class WorldWindow
  {
    typedef function<void (int, int, int, int)> kpListener;
    typedef function<void (int, int)> fbListener;
    typedef function<void (double)> opListener;
    typedef function<void (int, int, int)> mbListener;

    GLFWwindow*        pWindow;
    int                width;
    int                height;
    bool               vsync;
    double             lastTime;
    vector<kpListener> kpListeners;
    vector<fbListener> fbListeners;
    vector<opListener> opListeners;
    vector<mbListener> mbListeners;

    void init(const string& name, int width, int height);

    static void keyCallback_Thunk(GLFWwindow* pWindow, int key,
      int scancode, int action, int mods);
    static void framebufferResizeCallback_Thunk(GLFWwindow* pWindow,
      int width, int height);
    static void mouseButtonCallback_Thunk(GLFWwindow* pWindow,
      int button, int action, int mods);
    static void errorCallback(int error, const char* desc);

  public:
    WorldWindow(const string& name, int width, int height);
    WorldWindow(const string& name);
    virtual ~WorldWindow();
    void run();
    GLFWwindow* getWindow() const;
    int getWidth() const;
    int getHeight() const;
    bool getVsync() const;
    void setVsync(bool vsync);
    virtual void onKeypress(int key, int scancode, int action, int mods);
    virtual void onFramebufferResize(int width, int height);
    virtual void onPulse();
    virtual void onMouseButton(int button, int action, int mods);
    void onKeypress(kpListener eventListener);
    void onPulse(opListener eventListener);
    void onFramebufferResize(fbListener eventListener); 
    void onMouseButton(mbListener eventListener);
    pair<double, double> getCursorPos() const;
    void setCursorPos(double xPos, double yPos);
    void hideCursor() const;
    void showCursor() const;
  };
}

#endif

