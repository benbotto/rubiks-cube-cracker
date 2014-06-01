#ifndef _BUSYBIN_CAMERA_H_
#define _BUSYBIN_CAMERA_H_

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
using glm::rotate;
using glm::normalize;
using glm::lookAt;

namespace busybin
{
  /**
   * The camera in the World.
   */
  class Camera
  {
    const static float moveDelta;
    const static float yawDelta;
    const static float pitchDelta;

    vec3   location;
    vec3   U;
    vec3   V;
    vec3   N;
    mat4   view;

    Camera(const Camera& Camera);
    void operator=(const Camera&);
  protected:
  public:
    Camera();
    void look();
    void moveForward(double elapsed);
    void moveBackward(double elapsed);
    void moveUp(double elapsed);
    void moveDown(double elapsed);
    void strafeLeft(double elapsed);
    void strafeRight(double elapsed);
    void pitch(double elapsed, int deltaY);
    void yaw(double elapsed, int deltaX);
    mat4 getView() const;
    void setLocation(const vec3& position);
  };
}

#endif

