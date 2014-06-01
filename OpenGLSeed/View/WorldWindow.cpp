#include "WorldWindow.h"

namespace busybin
{
  /**
   * Create the window in windowed mode with the given width and height.
   * @param name The window title.
   * @param width The width of the window.
   * @param height The height of the window.
   */
  WorldWindow::WorldWindow(const string& name, int width, int height)
  {
    init(name, width, height);
  }

  /**
   * Create the window in full-screen mode.
   * @param name The window title.
   */
  WorldWindow::WorldWindow(const string& name)
  {
    init(name, 0, 0);
  }

  /**
   * Initialize GLFW.
   * @param name The window title.
   * @param width The width of the window.
   * @param height The height of the window.
   */
  void WorldWindow::init(const string& name, int width, int height)
  {
    // Initialize glfw.
    if (!glfwInit())
      throw GLException("Failed to initialize glfw.");

    // Use OpenGL 3.3, and don't bring in the old OpenGL stuff.
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti aliasing.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window in windowed mode.
    if (width && height)
    {
      if (!(this->pWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL)))
        throw GLException("Failed to create window.");
    }
    // Create the window in full-screen mode.
    else
    {
      // Get the primary monitor and desktop video mode.
      GLFWmonitor* primary    = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = glfwGetVideoMode(primary);

      // Use the maximum refresh rate.
      glfwWindowHint(GLFW_REFRESH_RATE, 0);

      if (!(this->pWindow = glfwCreateWindow(mode->width, mode->height,
        name.c_str(), primary, NULL)))
        throw GLException("Failed to create full-screen window.");
    }

    // Make the new context the current one.
    glfwMakeContextCurrent(this->pWindow);

    // Initialize GLEW, the OpenGL loader.
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
      throw GLException("Falied to initialize GLEW.");

    if (glGetError() != GL_INVALID_ENUM)
      throw GLException("glewInit raised a GL_ERROR.");

    // Listen for key events.
    glfwSetWindowUserPointer(this->pWindow, this);
    glfwSetKeyCallback(this->pWindow, this->keyCallback_Thunk);

    // Listen for resize events.
    glfwSetFramebufferSizeCallback(this->pWindow, this->framebufferResizeCallback_Thunk);

    // Listen for clicks.
    glfwSetMouseButtonCallback(this->pWindow, this->mouseButtonCallback_Thunk);

    // Listen for errors.
    glfwSetErrorCallback(this->errorCallback);

    // Initialize the viewport.
    glfwGetFramebufferSize(this->pWindow, &this->width, &this->height);
    glViewport(0, 0, this->width, this->height);

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to set viewport.");

    // Enable depth test so that the back of objects is hidden.
    glEnable(GL_DEPTH_TEST);

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to enable depth test.");

    // Vertical sync.
    this->setVsync(true);

    // Initialize the time.
    this->lastTime = glfwGetTime();
  }

  /**
   * Destroy the window.
   */
  WorldWindow::~WorldWindow()
  {
    glfwDestroyWindow(this->pWindow);
    glfwTerminate();
  }

  /**
   * Run the main loop.
   */
  void WorldWindow::run()
  {
    while (!glfwWindowShouldClose(this->pWindow))
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      onPulse();
      glfwSwapBuffers(this->pWindow);
      glfwPollEvents();
    }
  }

  /**
   * Get the window.
   */
  GLFWwindow* WorldWindow::getWindow() const
  {
    return this->pWindow;
  }

  /**
   * Get the framebuffer width.
   */
  int WorldWindow::getWidth() const
  {
    return this->width;
  }

  /**
   * Get the framebuffer height.
   */
  int WorldWindow::getHeight() const
  {
    return this->height;
  }

  /**
   * Get the vsync status.
   */
  bool WorldWindow::getVsync() const
  {
    return this->vsync;
  }

  /**
   * Enable/Disable vsycn.
   * @param vsync True if vsync should be on (it's on by default).
   */
  void WorldWindow::setVsync(bool vsync)
  {
    this->vsync = vsync;

    if (this->vsync)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);
  }

  /**
   * Fires when a key is pressed.  Subclasses should implement this.  By 
   * default this does nothing.
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action For example, GLFW_PRESS.
   * @param mods Modifiers like alt.
   */
  void WorldWindow::onKeypress(int key, int scancode, int action, int mods)
  {
    // Fire the listeners.
    for (kpListener& f : this->kpListeners)
      f(key, scancode, action, mods);
  }

  /**
   * Wire up a keypress listener.
   * @param eventListener Listener for keypress events
   *        function<void (int, int, int, int)>.
   */
  void WorldWindow::onKeypress(function<void (int, int, int, int)> eventListener)
  {
    this->kpListeners.push_back(eventListener);
  }

  /**
   * Fires when the framebuffer is resized.  Retrieves the client area of the 
   * window in pixels.  This is more widly supported (MAC OS for example needs
   * to use this).  This updates the viewport (glViewport).
   * @param width The new window width.
   * @param height The new window height.
   */
  void WorldWindow::onFramebufferResize(int width, int height)
  {
    this->width  = width;
    this->height = height;

    // Set the viewport.
    glViewport(0, 0, width, height);
    
    // Fire the listeners.
    for (fbListener& f : this->fbListeners)
      f(width, height);
  }

  /**
   * Add a listener to the onFramebufferSize event.
   * @param eventListener An event listener function that will receive
   *        the width and the height, in pixels, of the frame buffer.
   */
  void WorldWindow::onFramebufferResize(function<void (int, int)> eventListener)
  {
    this->fbListeners.push_back(eventListener);
  }

  /**
   * Called on every iteration of the game loop.
   */
  void WorldWindow::onPulse()
  {
    double time = glfwGetTime();
    double elapsed = time - this->lastTime;

    this->lastTime = time;

    // Fire the listeners.
    for (opListener& f : this->opListeners)
      f(elapsed);
  }

  /**
   * Add a pulse listener (fires every iteration of the main game loop).
   * @param eventListener The listener function<void(double)> that gets called
   *        with the elapsed time since GLFW was initialized.
   */
  void WorldWindow::onPulse(opListener eventListener)
  {
    this->opListeners.push_back(eventListener);
  }

  /**
   * Fires when a mouse button is clicked.
   * @param button The GLFW_MOUSE_BUTTON_n that was pressed.
   * @param action GLFW_PRESS or GLFW_RELEASE.
   * @param mods Modifier keys bit mask.
   */
  void WorldWindow::onMouseButton(int button, int action, int mods)
  {
    // Fire the listeners.
    for (mbListener& f : this->mbListeners)
      f(button, action, mods);
  }

  /**
   * Add a mouse button listener.
   * @param eventListener The listener function<void(int, int, int)>.
   */
  void WorldWindow::onMouseButton(mbListener eventListener)
  {
    this->mbListeners.push_back(eventListener);
  }

  /**
   * Get the cursor position (x, y), relative to the top-left corner of the 
   * drawing area of the window.
   */
  pair<double, double> WorldWindow::getCursorPos() const
  {
    double xPos;
    double yPos;

    // Get the mouse position.
    glfwGetCursorPos(this->pWindow, &xPos, &yPos);

    return make_pair(xPos, yPos);
  }

  /**
   * Set the cursor position.
   * @param xPos The x param.
   * @param yPos The y position.
   */
  void WorldWindow::setCursorPos(double xPos, double yPos)
  {
    glfwSetCursorPos(this->pWindow, xPos, yPos);
  }

  /**
   * Hide the cursor.
   */
  void WorldWindow::hideCursor() const
  {
    glfwSetInputMode(this->pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  /**
   * Show the cursor.
   */
  void WorldWindow::showCursor() const
  {
    glfwSetInputMode(this->pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  /**
   * Fires when a key is pressed.
   * @param pWindow The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action For example, GLFW_PRESS.
   * @param mods Modifiers like alt.
   */
  void WorldWindow::keyCallback_Thunk(GLFWwindow* pWindow, int key,
    int scancode, int action, int mods)
  {
    WorldWindow* pWW = static_cast<WorldWindow*>(glfwGetWindowUserPointer(pWindow));
    pWW->onKeypress(key, scancode, action, mods);
  }

  /**
   * Fires when the framebuffer is resized.  Retrieves the client area of the 
   * window in pixels.  This is more widly supported (MAC OS for example needs
   * to use this).
   * @param pWindow The window (same as this->pWindow).
   * @param width The new window width.
   * @param height The new window height.
   */
  void WorldWindow::framebufferResizeCallback_Thunk(GLFWwindow* pWindow,
    int width, int height)
  {
    WorldWindow* pWW = static_cast<WorldWindow*>(glfwGetWindowUserPointer(pWindow));
    pWW->onFramebufferResize(width, height);
  }

  /**
   * Fires when a mouse button is clicked.
   * @param pWindow The window.
   * @param button The GLFW_MOUSE_BUTTON_n that was pressed.
   * @param action GLFW_PRESS or GLFW_RELEASE.
   * @param mods Modifier keys bit mask.
   */
  void WorldWindow::mouseButtonCallback_Thunk(GLFWwindow* pWindow,
    int button, int action, int mods)
  {
    WorldWindow* pWW = static_cast<WorldWindow*>(glfwGetWindowUserPointer(pWindow));
    pWW->onMouseButton(button, action, mods);
  }

  /**
   * Fires when an error occurs and throws an exception.
   * @param error The error code.
   * @param desc The error description.
   */
  void WorldWindow::errorCallback(int error, const char* desc)
  {
    throw GLException(desc);
  }
}

