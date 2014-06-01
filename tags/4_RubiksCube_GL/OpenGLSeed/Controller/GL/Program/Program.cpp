#include "Program.h"

namespace busybin
{
  /**
   * Initialize the Program.
   * @param name The program name.
   */
  Program::Program(const string& name)
  {
    this->linked = false;
    this->name   = name;

    // Create the program.
    this->programID = glCreateProgram();

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to create program.");
  }

  /**
   * Cleanup.
   */
  Program::~Program()
  {
    // Delete VBOs.
    for (unsigned vbo : this->buffers)
      glDeleteBuffers(1, &vbo);

    // Delete VAOs.
    for (unsigned vao : this->vaos)
      glDeleteVertexArrays(1, &vao);
  }

  /**
   * Get the program id.
   */
  int Program::getProgramID() const
  {
    return this->programID;
  }

  /**
   * Get the program name.
   */
  string Program::getName() const
  {
    return this->name;
  }

  /**
   * Add a shader to the program.
   * @param shader The shader to attach.
   */
  void Program::addShader(const Shader& shader)
  {
    this->linked = false;

    if (this->shaders.count(shader.getShaderID()))
      throw GLException("Shader already attached.");

    // Add the shader to the list.
    this->shaders.insert(std::pair<int, Shader>(shader.getShaderID(), shader));

    // Attach the shader to the program.
    glAttachShader(this->getProgramID(), shader.getShaderID());

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to attach shader.");
  }

  /**
   * Get a copy of the shader with the shader id shaderID.
   * @param shaderID The ID of the shader.
   */
  Shader Program::getShader(int shaderID) const
  {
    shaderMap::const_iterator it = this->shaders.find(shaderID);

    if (it == this->shaders.end())
      throw GLException("Failed to find shader.");

    return it->second;
  }

  /**
   * Link the shaders into a program.
   */
  void Program::link()
  {
    int linkStat;

    if (!this->shaders.size())
      throw GLException("There are no shaders.");

    // Link the program.
    glLinkProgram(this->getProgramID());

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to link program.");

    // Check the linker status.
    glGetProgramiv(this->getProgramID(), GL_LINK_STATUS, &linkStat);

    if (linkStat != GL_TRUE)
    {
      ostringstream exLog;
      const int     max = 1024;
      char          infoLog[max + 1];
      int           len;

      exLog << "Attempt to link program returned GL_FALSE.  Log:\n\n";

      glGetProgramInfoLog(this->getProgramID(), max, &len, infoLog);
      exLog << infoLog << '\n';
    
      throw GLException(exLog.str());
    }
    else
      this->linked = true;
  }

  /**
   * Install the shader program (i.e. use it).
   */
  void Program::install()
  {
    // Make sure the program is linked.
    if (!this->linked)
      throw GLException("Program not linked.");

    // Use the program.
    glUseProgram(this->getProgramID());

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to install program.");
  }

  /**
   * Find a shader attribute.
   */
  int Program::findAttribute(const string& attrName) const
  {
    int pos = glGetAttribLocation(this->getProgramID(), attrName.c_str());

    if (glGetError() != GL_NO_ERROR)
    {
      string err = "Attempt to locate attribute \"";
      err += attrName;
      err += "\" failed.";
      throw GLException(err);
    }

    if (pos == -1)
    {
      string err = "Failed to find attribute \"";
      err += attrName;
      err += "\".";
      throw GLException(err);
    }

    return pos;
  }

  /**
   * Find a uniform variable.
   */
  int Program::findUniform(const string& attrName) const
  {
    int pos   = glGetUniformLocation(this->getProgramID(), attrName.c_str());
    int eCode = glGetError();

    if (eCode != GL_NO_ERROR)
    {
      ostringstream err;
      err << "Attempt to locate uniform \"" <<  attrName
          << "\" failed.  Pos is: " << pos << ".  Error is: "
          << eCode;
      throw GLException(err.str());
    }

    if (pos == -1)
    {
      string err = "Attempt to locate uniform \"";
      err += attrName;
      err += "\" failed.";
      throw GLException(err);
    }

    return pos;
  }

  /**
   * Enable a uniform variable.
   */
  void Program::enableUniform(const string& uniformName) const
  {
    int u = this->findUniform(uniformName);
    glUniform1i(u, true);
  }

  /**
   * Disable a uniform variable.
   */
  void Program::disableUniform(const string& uniformName) const
  {
    int u = this->findUniform(uniformName);
    glUniform1i(u, false);
  }

  /**
   * Set the model matrix.
   */
  void Program::setModel(const mat4& model) const
  {
    glUniformMatrix4fv(this->getModelAttr(), 1, GL_FALSE, value_ptr(model));
  }

  /**
   * Set the view matrix.
   */
  void Program::setView(const mat4& view) const
  {
    glUniformMatrix4fv(this->getViewAttr(), 1, GL_FALSE, value_ptr(view));
  }

  /**
   * Set the projection matrix.
   */
  void Program::setProjection(const mat4& projection) const
  {
    glUniformMatrix4fv(this->getProjectionAttr(), 1, GL_FALSE, value_ptr(projection));
  }

  /**
   * Set the MVP from a MatrixStack.  Uses the top of all stacks.
   * @param matrixStack The World's MatrixStack.
   */
  void Program::setMVP(const MatrixStack& matrixStack) const
  {
    this->setModel(matrixStack.topModel());
    this->setView(matrixStack.topView());
    this->setProjection(matrixStack.topProjection());
  }

  /**
   * Check if the program is linked.
   */
  bool Program::isLinked()
  {
    return this->linked;
  }

  /**
   * Create a buffer (VBO) and fill it.
   * @param fillWith The array which will fill the buffer.
   * @param buffSize The size in bytes of the fillWith array.
   * @param elementsPerVec The number of elements per vector.
   * @param vertexAttrib The vertex attribute to point at the buffer.
   * @param vao The vertex array object ID.
   */
  void Program::createAndFillBuffer(const void* const fillWith,
    unsigned buffSize, unsigned elementsPerVec, int vertexAttrib,
    unsigned vao)
  {
    // Bind the vertex array for vertex insertion.
    glBindVertexArray(vao);

    // Create the buffer.
    this->buffers.push_back(0);
    glGenBuffers(1, &this->buffers.back());

    // Set up the vertex position buffer.
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.back());

    // Fill the buffer with the vertices.
    glBufferData(GL_ARRAY_BUFFER, buffSize, fillWith, GL_STATIC_DRAW);
    
    // Enable the vertex attribute.
    glEnableVertexAttribArray(vertexAttrib);

    // Point the vertex attribute to the beginning of the buffer.
    glVertexAttribPointer(vertexAttrib, elementsPerVec, GL_FLOAT, GL_FALSE, 0, 0);

    // Deactivate the VAO.
    glBindVertexArray(0);
  }

  /**
   * Create and fill a buffer with an array of glm::vec3.
   * @param fillWith The array which will fill the buffer.
   * @param vertexAttrib The vertex attribute to point at the buffer.
   * @param vao The vertex array object ID.
   */
  void Program::createAndFillBuffer(vector<vec3>& fillWith,
    int vertexAttrib, unsigned vao)
  {
    // Set up and fill the vertex buffer.
    createAndFillBuffer(value_ptr(fillWith.at(0)),
      sizeof(vec3) * fillWith.size(), 3, vertexAttrib, vao);
  }

  /**
   * Create and fill a buffer with an array of glm::vec4.
   * @param fillWith The array which will fill the buffer.
   * @param vertexAttrib The vertex attribute to point at the buffer.
   * @param vao The vertex array object ID.
   */
  void Program::createAndFillBuffer(vector<vec4>& fillWith,
    int vertexAttrib, unsigned vao)
  {
    // Set up and fill the vertex buffer.
    createAndFillBuffer(value_ptr(fillWith.at(0)),
      sizeof(vec4) * fillWith.size(), 4, vertexAttrib, vao);
  }

  /**
   * Generate a vertex array object.  It will be auto deleted on DTOR.
   */
  unsigned Program::generateVertexArrayObject()
  {
    unsigned vao;
    glGenVertexArrays(1, &vao);
    this->vaos.push_back(vao);
    return vao;
  }

  /**
   * Draw the arrays pointed to by the VAO.
   * @param vao The vertex array object to bind.
   * @param count The number of indices to render.
   * @param mode The kind of primitive to render.  Defaults to GL_TRIANGLES.
   */
  void Program::drawArrays(unsigned vao, unsigned count, GLenum mode) const
  {
    // Bind the vertex array for vertex insertion.
    glBindVertexArray(vao);

    // Draw the arrays.
    glDrawArrays(mode, 0, count);
  }

  /**
   * Set a uniform in the program.
   * @param uniformName The name of the uniform.
   * @param matrix A glm::mat4 matrix.
   */
  void Program::setUniform(const string& uniformName, const mat4& matrix) const
  {
    int uID = this->findUniform(uniformName);
    glUniformMatrix4fv(uID, 1, GL_FALSE, value_ptr(matrix));
  }

  /**
   * Set a uniform in the program.
   * @param uniformName The name of the uniform.
   * @param vector A glm::vec3 vector.
   */
  void Program::setUniform(const string& uniformName, const vec3& vector) const
  {
    int uID = this->findUniform(uniformName);
    glUniform3fv(uID, 1, value_ptr(vector));
  }

  /**
   * Set a uniform in the program.
   * @param uniformName The name of the uniform.
   * @param vector A glm::vec3 vector.
   */
  void Program::setUniform(const string& uniformName, const vec4& vector) const
  {
    int uID = this->findUniform(uniformName);
    glUniform4fv(uID, 1, value_ptr(vector));
  }

  /**
   * Set a uniform in the program.
   * @param uniformName The name of the uniform.
   * @param val A float value.
   */
  void Program::setUniform(const string& uniformName, float val) const
  {
    int uID = this->findUniform(uniformName);
    glUniform1f(uID, val);
  }
}

