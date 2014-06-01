#include "Shader.h"

namespace busybin
{
  /**
   * Initialize the shader.
   * @param fileName A GLSL shader program that will be used to create 
   * the shader.
   * @param shaderType The type of shader (GL_VERTEX_SHADER or 
   * GL_FRAGMENT_SHADER).
   */
  Shader::Shader(const string& fileName, int shaderType)
  {
    vector<string> fileNames(1, fileName);
    this->initialize(fileNames, shaderType);
  }

  /**
   * Initialize the Shader.
   * @param fileNames A vector of files names that will be used to create the
   * shader.
   * @param shaderType The type of shader (GL_VERTEX_SHADER or 
   * GL_FRAGMENT_SHADER).
   */
  Shader::Shader(const vector<string>& fileNames, int shaderType)
  {
    this->initialize(fileNames, shaderType);
  }

  /**
   * Initialize the Shader (builder pattern for the constructors).
   * @param fileNames A vector of files names that will be used to create the
   * shader.
   * @param shaderType The type of shader (GL_VERTEX_SHADER or 
   * GL_FRAGMENT_SHADER).
   */
  void Shader::initialize(const vector<string>& fileNames, int shaderType)
  {
    vector<string>::iterator source;
    vector<string>           sources;
    ifstream                 file;
    string                   line;
    int                      compStat;
    vector<int>              lengths;
    vector<const char*>      cSources;

    // Basic initialization.
    this->shaderType = shaderType;

    if (this->shaderType != GL_VERTEX_SHADER && this->shaderType != GL_FRAGMENT_SHADER)
      throw GLException("Invalid shader type.");

    // Create the shader.
    this->shaderID = glCreateShader(this->shaderType);

    if (!this->shaderID)
      throw GLException("Failed to create shader.");

    sources.resize(fileNames.size());
    source = sources.begin();

    // Read each file.
    for (vector<string>::const_iterator it = fileNames.begin(); it != fileNames.end(); ++it)
    {
      file.open(it->c_str());

      if (!file)
        throw GLException("Failed to open GLSL file.");

      // Reserve enough space for the source.
      file.seekg(0, std::ios::end);   
      source->reserve(file.tellg());
      file.seekg(0, std::ios::beg);

      // Read the source (parens are necessary).
      source->assign((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

      file.clear();
      file.close();
      ++source;
    }

    // Create c-strings from the source.
    cSources.resize(sources.size());
    transform(sources.begin(), sources.end(),
      cSources.begin(), mem_fun_ref(&string::c_str));

    // Create the lengths array (the lengths of the source files).
    lengths.resize(sources.size());
    transform(sources.begin(), sources.end(),
      lengths.begin(), mem_fun_ref(&string::length));
    
    // Provide the source for the shader.
    glShaderSource(this->shaderID, cSources.size(),
      cSources.data(), lengths.data());

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to use shader source.");

    // Compile the shader.
    glCompileShader(this->shaderID);

    if (glGetError() != GL_NO_ERROR)
      throw GLException("Failed to compile shader.");

    // Check the compilation status.
    glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &compStat);

    if (compStat != GL_TRUE)
    {
      ostringstream exLog;
      const int     max = 1024;
      char          infoLog[max + 1];
      int           len;

      exLog << "Attempt to compile shader returned GL_FALSE.  Log:\n\n";

      glGetShaderInfoLog(this->shaderID, max, &len, infoLog);
      exLog << infoLog << '\n';
    
      throw GLException(exLog.str());
    }
  }

  /**
   * Get the shader type.
   */
  int Shader::getShaderType() const
  {
    return this->shaderType;
  }

  /**
   * Get the shader id.
   */
  int Shader::getShaderID() const
  {
    return this->shaderID;
  }
}

