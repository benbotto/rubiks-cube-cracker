#include "WorldObject.h"

namespace busybin
{
  /**
   * Initialize the vertices.
   */
  WorldObject::Triangle::Triangle()
  {
    this->vertices.resize(3);
  }

  /**
   * Initialize the triangle.  The vertices should be clokwise.
   * @param v0 Vertex0.
   * @param v1 Vertex1.
   * @param v2 Vertex2.
   */
  WorldObject::Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
  {
    setVertices(v0, v1, v2);
  }

  /**
   * Set the vertices.  The vertices should be clockwise.
   * @param v0 Vertex0.
   * @param v1 Vertex1.
   * @param v2 Vertex2.
   */
  void WorldObject::Triangle::setVertices(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
  {
    this->vertices.at(0) = v0;
    this->vertices.at(1) = v1;
    this->vertices.at(2) = v2;
  }

  /**
   * Calculate the face normal.
   */
  void WorldObject::Triangle::computeNormal()
  {
    glm::vec3 U = vertices.at(0) - vertices.at(2);
    glm::vec3 V = vertices.at(0) - vertices.at(1);

    this->faceNormal = glm::normalize(glm::cross(U, V));
  }

  /**
   * Get the face normal.
   */
  glm::vec3 WorldObject::Triangle::getFaceNormal() const
  {
    return faceNormal;
  }

  /**
   * Get a vector that's tangent to the face normal.
   */
  glm::vec3 WorldObject::Triangle::getTangent() const
  {
    if (fabs(vertices.at(1).x) < .0001 && fabs(vertices.at(1).z)< .0001)
    {
      if (vertices.at(1).y > 0)
        return glm::vec3(1.0f, 0.0f, 0.0f);
      else
        return glm::vec3(-1.0f, 0.0f, 0.0f);
    }

    if (vertices.at(2).y > vertices.at(1).y)
      return vertices.at(1) - vertices.at(0);
    else
      return vertices.at(2) - vertices.at(0);
  }
}
