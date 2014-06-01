#include "Camera.h"

namespace busybin
{
  const float Camera::moveDelta  = 12.75f;
  const float Camera::yawDelta   = -.425f;
  const float Camera::pitchDelta = -.425f;

  /**
   * Initialize the location, U, V, and N vectors.  The Camera starts at 10 on
   * the Z axis, looking in the negative Z direction.  The camera coordinate
   * system is left-handed, so the positive X is to the right in both camera
   * and world coordinates.
   */
  Camera::Camera() : 
    location(0.0f, 0.0f, 9.0f), // Location
    U(1.0f, 0.0f,  0.0f),       // X
    V(0.0f, 1.0f,  0.0f),       // Y
    N(0.0f, 0.0f, -1.0f)        // Z
  {
    // Calcluate the initial view.
    this->look();
  }

  /**
   * Prevent copies.
   */
  Camera::Camera(const Camera& Camera) { }

  /**
   * Prevent copies.
   */
  void Camera::operator=(const Camera&) { }

  /**
   * Apply the look.
   */
  void Camera::look()
  {
    // Look 3 units in front of the location.
    vec3 normLook = normalize(this->N);
    vec3 look     = this->location + (normLook * 3.0f);

    // Calculate the view matrix.
    this->view = lookAt(this->location, look, this->V);
  }

  /**
   * Move the camera forward by moveDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::moveForward(double elapsed)
  {
    // Normalize the lookat (N).
    vec3 viewDir = normalize(this->N);

    // Update the location with moveDelta added.
    this->location += viewDir * moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Move the camera backward by moveDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::moveBackward(double elapsed)
  {
    // Normalize the lookat (N).
    vec3 viewDir = normalize(this->N);

    // Update the location with moveDelta added.
    this->location += viewDir * -moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Move the camera up by moveDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::moveUp(double elapsed)
  {
    // Normalize the up (V).
    vec3 upDir = normalize(this->V);

    // Update the location with moveDelta added.
    this->location += upDir * moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Move the camera down by moveDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::moveDown(double elapsed)
  {
    // Normalize the up (V).
    vec3 upDir = normalize(this->V);

    // Update the location with moveDelta added.
    this->location += upDir * -moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Stafe left.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::strafeLeft(double elapsed)
  {
    // Normalize the U (the left/right axis).
    vec3 xDir = normalize(this->U);

    // Update the location with moveDelta added.
    this->location += xDir * -moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Stafe right.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Camera::strafeRight(double elapsed)
  {
    // Normalize the U (the left/right axis).
    vec3 xDir = normalize(this->U);

    // Update the location with moveDelta added.
    this->location += xDir * moveDelta * (float)elapsed;

    this->look();
  }

  /**
   * Pitch by deltaY * pitchDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   * @param deltaY The difference in the Y direction, multiplied by pitchDelta.
   */
  void Camera::pitch(double elapsed, int deltaY)
  {
    // Rotate the up (V) and look (N) about the right (U) axis.
    mat4 rotation = rotate(mat4(1.0f), deltaY * pitchDelta * (float)elapsed, this->U);

    this->V = vec3(rotation * vec4(this->V, 1.0f));
    this->N = vec3(rotation * vec4(this->N, 1.0f));

    this->look();
  }

  /**
   * Yaw by deltax * yawDelta.
   * @param elapsed The number of elapsed seconds since the last pulse.
   * @param deltaX The difference in the X direction, multiplied by yawDelta.
   */
  void Camera::yaw(double elapsed, int deltaX)
  {
    // Rotate the right (U) and look (N) about the up (V) axis.
    mat4 rotation = rotate(mat4(1.0f), deltaX * yawDelta * (float)elapsed, this->V);

    this->U = vec3(rotation * vec4(this->U, 1.0f));
    this->N = vec3(rotation * vec4(this->N, 1.0f));

    this->look();
  }

  /**
   * Get the current view for the MVP.
   */
  mat4 Camera::getView() const
  {
    return this->view;
  }

  /**
   * Set the Camera's position.
   * @param location The new location of the Camera.
   */
  void Camera::setLocation(const vec3& location)
  {
    this->location = location;
  }
}

