#include "Torus.h"

namespace busybin
{
  /**
   * Create the Torus vertices.
   * @param innerRadius The inner radius of the torus.
   * @param outerRadius The outer radius of the torus.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   * @param name The name of the Torus.
   * @param numTriangleStrips The number of vertical square strips.
   * @param colors The 2 colors of the torus.
   */
  Torus::Torus(float innerRadius, float outerRadius, Program* pProgram,
    MatrixStack* pMatrixStack, const string& name,
    unsigned numTriangleStrips, vector<vec4> colors) :
    WorldObject(name, pProgram, pMatrixStack)
  {
    mat4                  translationX;
    vec3                  start(0.0f, (outerRadius - innerRadius) / 2, 0.0f);
    vec3                  zAxis(0.0f, 0.0f, 1.0f);
    vec3                  yAxis(0.0f, 1.0f, 0.0f);
    vector<vec4>          colorToggle;
    vector<vector<vec3> > holdVerts;

    holdVerts.reserve(numTriangleStrips);

    translationX = translate(mat4(1.0f),
      vec3(innerRadius + (outerRadius - innerRadius) / 2, 0.0f, 0.0f));

    // Rotate about the y axis at 360/numTriangleStrips intervals.
    for (unsigned level = 0; level < numTriangleStrips; ++level)
    {
      float angleY = pi<float>() * 2 / numTriangleStrips * level;
      mat4 rotationY = rotate(mat4(1.0f), angleY, yAxis);

      holdVerts.push_back(vector<vec3>());
      holdVerts.back().reserve(numTriangleStrips);

      // Each y rotation, rotate 360 degrees about z, making vertices at
      // 360 / numTriangleStrips intevals.
      for (unsigned v = 0; v < numTriangleStrips; ++v)
      {
        float angleZ = pi<float>() * 2 / numTriangleStrips * v;
        mat4 rotationZ = rotate(mat4(1.0f), angleZ, zAxis);

        holdVerts.back().push_back(vec3(rotationY * translationX * rotationZ * vec4(start, 1.0f)));
      }
    }

    // The number of vertices will be numTriangleStrips * 
    // numTriangles / quadStrip * numVerticesPerTriangle.
    this->vertices.reserve(numTriangleStrips * numTriangleStrips * 2 * 3);

    // Set up the colors (stripes).
    this->setColors(colors, 2);
    colorToggle.push_back(this->colors.at(0));
    colorToggle.push_back(this->colors.at(1));
    this->colors.clear();
    this->colors.reserve(this->vertices.size());

    /**
     * Convert the vertices to a series of triangles.  When
     * numTriangleStrips = 4, then this is one level of the torus.
     *
     * 0----1----2----3----0
     * |   /|   /|   /|   /|
     * |  / |  / |  / |  / |
     * | /  | /  | /  | /  |
     * |/   |/   |/   |/   |
     * 0----1----2----3----0
     *            
     *    level = [0,0,1],[0,0,1],[0,0,1],[0,0,1] , [1,1,0],[1,1,0],[1,1,0],[1,1,0]
     * vertices = [0,1,0],[1,2,1],[2,3,2],[3,0,3] , [1,0,1],[2,1,2],[3,2,3],[0,3,0]
     */
    for (unsigned level = 0; level < holdVerts.size(); ++level)
    {
      int nextLevel   = (level + 1) % holdVerts.size();
      vec4 color = colorToggle.at(level % 2);

      for (unsigned v = 0; v < holdVerts.at(level).size(); ++v)
      {
        int nextV = (v + 1) % holdVerts.at(level).size();

        // The vertices are pushed clock-wise for normal vertex computation.
        this->vertices.push_back(holdVerts.at(level).at(v));
        this->vertices.push_back(holdVerts.at(level).at(nextV));
        this->vertices.push_back(holdVerts.at(nextLevel).at(v));

        this->vertices.push_back(holdVerts.at(nextLevel).at(nextV));
        this->vertices.push_back(holdVerts.at(nextLevel).at(v));
        this->vertices.push_back(holdVerts.at(level).at(nextV));

        this->colors.resize(this->colors.size() + 6, color);
      }
    }

    // Compute the normals for each vertex.
    computeVertexNormals();

    // Set up and fill the vertex buffer, color buffer, and normal buffer.
    this->getProgram()->createAndFillBuffer(this->vertices,
      this->getProgram()->getVertexPositionAttr(), this->getVAO());
    this->getProgram()->createAndFillBuffer(this->vertexNormals,
      this->getProgram()->getVertexNormalAttr(), this->getVAO());
    this->getProgram()->createAndFillBuffer(this->colors,
      this->getProgram()->getVertexColorAttr(), this->getVAO());
  }
}

