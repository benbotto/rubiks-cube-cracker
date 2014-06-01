#ifndef _BUSYBIN_WORLD_OBJECT_H_
#define _BUSYBIN_WORLD_OBJECT_H_

#define GLM_FORCE_RADIANS

#include "../../Util/GLException.h"
#include "../../Util/VectorHelper.h"
#include "../../Controller/GL/Program/Program.h"
#include "../MatrixStack.h"
#include "../Material/Material.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::multimap;
#include <utility>
using std::pair;
#include <memory>
using std::unique_ptr;
using std::move;
#include <cmath>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;
#include <glm/gtc/matrix_transform.hpp>
using glm::normalize;

namespace busybin
{
  /**
   * A basic world object (some visual graphic in the world).
   */
  class WorldObject
  {
    string       name;
    mat4         model;
    unsigned     vao;
    Program*     pProgram;
    MatrixStack* pMatrixStack;

    /**
     * This class is used as a helper for vertex normal generation.
     */
    class Triangle
    {
      vector<vec3> vertices;
      vec3         faceNormal;
      vec3         tangent;

    public:
      Triangle();
      Triangle(vec3 v0, vec3 v1, vec3 v2);
      void setVertices(vec3 v0, vec3 v1, vec3 v2);
      void computeNormal();
      vec3 getFaceNormal() const;
      vec3 getTangent() const;
    };

  protected:
    typedef unique_ptr<Material> matPtr;

    vector<vec3> vertices;
    vector<vec3> vertexNormals;
    vector<vec3> vertexTangents;
    vector<vec4> colors;
    matPtr       material;

    virtual void setColors(vector<vec4>& colors, unsigned min = 1);
    virtual void computeVertexNormals();

  public:
    WorldObject(const string& name, Program* pProgram, MatrixStack* pMatrixStack);
    virtual ~WorldObject();
    string getName() const;
    unsigned getVAO() const;
    virtual mat4 getModel() const;
    virtual void setModel(mat4 translation);
    virtual Program* getProgram() const;
    virtual Material& getMaterial() const;
    MatrixStack* getMatrixStack();
    virtual void setMaterial(unique_ptr<Material> material);
    virtual vector<vec4> getColors() const;
    virtual void draw(double elapsed) = 0;
  };
}

#endif

