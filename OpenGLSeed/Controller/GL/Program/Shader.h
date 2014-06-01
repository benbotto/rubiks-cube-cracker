#ifndef _BUSYBIN_SHADER_H_
#define _BUSYBIN_SHADER_H_

#include "../../../Util/GLException.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <vector>
using std::vector;
#include <memory>
using std::mem_fun_ref;
#include <algorithm>
using std::transform;

namespace busybin
{
  class Shader
  {
    int shaderType;
    int shaderID;
    void initialize(const vector<string>& fileNames, int shaderType);

  public:
    Shader(const string& fileName, int shaderType);
    Shader(const vector<string>& fileNames, int shaderType);
    int getShaderType() const;
    int getShaderID() const;
  };
}

#endif
