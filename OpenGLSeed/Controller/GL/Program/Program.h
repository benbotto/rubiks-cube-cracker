#ifndef _BUSYBIN_PROGRAM_H_
#define _BUSYBIN_PROGRAM_H_

#define GLM_FORCE_RADIANS

#include "Shader.h"
#include "../../../Util/GLException.h"
#include "../../../Model/MatrixStack.h"
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec4;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using glm::value_ptr;

namespace busybin
{
  /**
   * The class links one or more Shaders into a Program, which can then
   * be installed.
   */
  class Program
  {
    typedef map<int, Shader> shaderMap;

    int              programID;
    shaderMap        shaders;
    bool             linked;
    string           name;
    vector<unsigned> buffers;
    vector<unsigned> vaos;

  protected:
    void createAndFillBuffer(const void* const fillWith, unsigned buffSize,
      unsigned elementsPerVec, int vertexAttrib, unsigned vao);

  public:
    Program(const string& name);
    virtual ~Program();

    int getProgramID() const;
    string getName() const;

    int findAttribute(const string& attrName) const;
    int findUniform(const string& attrName) const;
    void enableUniform(const string& uniformName) const;
    void disableUniform(const string& uniformName) const;
    void setUniform(const string& uniformName, const mat4& matrix) const;
    void setUniform(const string& uniformName, const vec3& vector) const;
    void setUniform(const string& uniformName, const vec4& vector) const;
    void setUniform(const string& uniformName, float val) const;

    void setModel(const mat4& model) const;
    void setView(const mat4& view) const;
    void setProjection(const mat4& projection) const;
    void setMVP(const MatrixStack& matrixStack) const;

    void addShader(const Shader& shader);
    Shader getShader(int shaderID) const;

    void link();
    bool isLinked();
    void install();

    void createAndFillBuffer(vector<vec3>& fillWith,
      int vertexAttrib, unsigned vao);
    void createAndFillBuffer(vector<vec4>& fillWith,
      int vertexAttrib, unsigned vao);

    unsigned generateVertexArrayObject();
    void drawArrays(unsigned vao, unsigned count, GLenum mode = GL_TRIANGLES) const;

    virtual int getModelAttr() const = 0;
    virtual int getViewAttr() const = 0;
    virtual int getProjectionAttr() const = 0;
    virtual int getVertexPositionAttr() const = 0;
    virtual int getVertexColorAttr() const = 0;
    virtual int getVertexNormalAttr() const = 0;
  };
}

#endif

