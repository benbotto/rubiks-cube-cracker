#include "Cube.h"

namespace busybin
{
  /**
   * Initialize the Cube's vertices.
   * @param size The width/height of the cube.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   * @param name The name of the Cube.
   * @param colors 6 colors, one for each face, ordered top, left, front,
   *        right, back, down.
   */
  Cube::Cube(float size, Program* pProgram, MatrixStack* pMatrixStack,
    const string& name, vector<vec4> colors) :
    WorldObject(name, pProgram, pMatrixStack)
  {
    const unsigned numVertsPerFace = 6;
    const unsigned numFaces = 6;
    float dist = size / 2;
    vector<vec3> normals;

    // Basic initialization.
    this->size = size;

    // Reserve space for the vertices.  There are 6 vertices per face, 
    // and 6 faces.
    this->vertices.reserve(numFaces * numVertsPerFace);

    /*
     * Create the six faces.
     */

    // Top.
    this->buildRect(
      vec3(-dist, dist, -dist),
      vec3( dist, dist, -dist),
      vec3(-dist, dist,  dist),
      vec3( dist, dist,  dist),
      this->vertices);

    // Left.
    this->buildRect(
      vec3(-dist,  dist, -dist),
      vec3(-dist,  dist,  dist),
      vec3(-dist, -dist, -dist),
      vec3(-dist, -dist,  dist),
      this->vertices);

    // Front.
    this->buildRect(
      vec3(-dist,  dist, dist),
      vec3( dist,  dist, dist),
      vec3(-dist, -dist, dist),
      vec3( dist, -dist, dist),
      this->vertices);

    // Right.
    this->buildRect(
      vec3(dist,  dist,  dist),
      vec3(dist,  dist, -dist),
      vec3(dist, -dist,  dist),
      vec3(dist, -dist, -dist),
      this->vertices);

    // Back.
    this->buildRect(
      vec3( dist,  dist, -dist),
      vec3(-dist,  dist, -dist), 
      vec3( dist, -dist, -dist),
      vec3(-dist, -dist, -dist),
      this->vertices);

    // Down.
    this->buildRect(
      vec3(-dist, -dist,  dist),
      vec3( dist, -dist,  dist),
      vec3(-dist, -dist, -dist),
      vec3( dist, -dist, -dist),
      this->vertices);

    // Make sure there are six colors (use the passed in colors here).
    if (colors.size() == 0)
      colors = vector<vec4>(6, vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else
      colors.resize(6, colors.back());
    this->colors.reserve(this->vertices.size());

    // Add the colors, one color per face.
    for (vector<vec4>::iterator color = colors.begin(); color != colors.end(); ++color)
      this->colors.resize(this->colors.size() + numVertsPerFace, *color);

    // Create the vertex normals.
    normals.reserve(6);

    normals.push_back(vec3( 0.0f,  1.0f,  0.0f)); // Top.
    normals.push_back(vec3(-1.0f,  0.0f,  0.0f)); // Left.
    normals.push_back(vec3( 0.0f,  0.0f,  1.0f)); // Front.
    normals.push_back(vec3( 1.0f,  0.0f,  0.0f)); // Right.
    normals.push_back(vec3( 0.0f,  0.0f, -1.0f)); // Back
    normals.push_back(vec3( 0.0f, -1.0f,  0.0f)); // Down.

    // Set the normals for each vertex.
    this->vertexNormals.reserve(this->vertices.size());

    for (vector<vec3>::iterator norm = normals.begin(); norm != normals.end(); ++norm)
      this->vertexNormals.resize(this->vertexNormals.size() + numVertsPerFace, *norm);

    // Set up and fill the vertex buffer, color buffer, and normal buffer.
    this->getProgram()->createAndFillBuffer(this->vertices,
      this->getProgram()->getVertexPositionAttr(), this->getVAO());
    this->getProgram()->createAndFillBuffer(this->vertexNormals,
      this->getProgram()->getVertexNormalAttr(), this->getVAO());
    this->getProgram()->createAndFillBuffer(this->colors,
      this->getProgram()->getVertexColorAttr(), this->getVAO());
  }

  /**
   * Build a rectangle from the four points.  The vertices are appended to 
   * the end of vertBuff.
   * @param topLeft The top left vertex of the square.
   * @param topRight The top right vertex of the square.
   * @param bottomLeft The bottom left vertex of the square.
   * @param bottomRight The bottom right vertex of the square.
   * @param vertBuff The vertices are appended to this vector.
   */
  void Cube::buildRect(const vec3& topLeft, const vec3& topRight,
    const vec3& bottomLeft, const vec3& bottomRight,
    vector<vec3>& vertBuff)
  {
    /*
     * The triangles look like this.
     *
     * 0---1
     * |  /|
     * | / |
     * |/  |
     * 2---3
     *
     * Vertices are pushed CW.
     */
    vertBuff.reserve(vertBuff.size() + 6);

    vertBuff.push_back(bottomLeft);
    vertBuff.push_back(topLeft);
    vertBuff.push_back(topRight);

    vertBuff.push_back(bottomLeft);
    vertBuff.push_back(topRight);
    vertBuff.push_back(bottomRight);
  }
}

