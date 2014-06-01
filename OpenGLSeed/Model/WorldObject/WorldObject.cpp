#include "WorldObject.h"

namespace busybin
{
  /**
   * Initialize the WorldObject.
   * @param name The name of the world object.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   */
  WorldObject::WorldObject(const string& name, Program* pProgram,
    MatrixStack* pMatrixStack) : model(mat4(1.0f))
  {
    this->name          = name;
    this->pProgram      = pProgram;
    this->pMatrixStack  = pMatrixStack;
    this->vao           = this->pProgram->generateVertexArrayObject();
  }

  /**
   * Do-nothing destructor.
   */
  WorldObject::~WorldObject()
  {
  }

  /**
   * Get the object's name.
   */
  string WorldObject::getName() const
  {
    return this->name;
  }

  /**
   * Get the current model matrix.
   */
  mat4 WorldObject::getModel() const
  {
    return this->model;
  }

  /**
   * Transform this world object.
   * @param model The model matrix to apply.
   */
  void WorldObject::setModel(mat4 model)
  {
    this->model = model;
  }

  /**
   * Set the colors of this WorldObject.
   * @param colors The colors to use.  If colors.size() < min, the last color
   * is repeated.  If colors.size() > min, the extra colors are ignored.
   * @param min The minimum number of colors.
   */
  void WorldObject::setColors(vector<vec4>& colors, unsigned min)
  {
    // Make sure there are enough colors.
    if (colors.size() == 0)
      this->colors = vector<vec4>(min, vec4(1.0f, 1.0f, 1.0f, 1.0f));

    this->colors.resize(min, colors.back());
  }

  /**
   * Get the vector of colors.
   */
  vector<vec4> WorldObject::getColors() const
  {
    return this->colors;
  }

  /**
   * Get the VAO associated with this object.
   */
  unsigned WorldObject::getVAO() const
  {
    return this->vao;
  }

  /**
   * Get the shader program.
   */
  Program* WorldObject::getProgram() const
  {
    return this->pProgram;
  }

  /**
   * Get the MatrixStack.
   */
  MatrixStack* WorldObject::getMatrixStack()
  {
    return this->pMatrixStack;
  }

  /**
   * Compute the normal for each vertex by averaging the surrounding surface
   * normals.
   * This function has been heavily optimized for speed.  It works by
   * calculating the surface normals for all triangles in the vertices array.
   * It keeps an association of vertex to surface normal.  The complexity
   * is nearly linear.
   */
  void WorldObject::computeVertexNormals()
  {
    typedef bool (*vecComp_t)(const vec3&, const vec3&);
    typedef multimap<vec3, Triangle*, vecComp_t> vecTriMap_t;
    typedef pair<vec3, Triangle*>                vecTriPair_t;
    typedef pair<vecTriMap_t::iterator,
      vecTriMap_t::iterator>                     vecTriRange_t;
    typedef vector<vec3>::iterator               vecIt_t;

    vecTriMap_t      vecTriMap(VectorHelper::lessThan);
    vector<Triangle> triangles;
    Triangle         triangle;
    vecTriRange_t    vecRange;
    vecIt_t          norm;
    vecIt_t          tan;

    triangles.reserve(this->vertices.size() / 3);

    // Calculate all the face normals.
    for (unsigned i = 0; i < this->vertices.size(); i += 3)
    {
      // Create the triangle and calculate the normal.
      triangle.setVertices(this->vertices.at(i), this->vertices.at(i + 1), this->vertices.at(i + 2));
      triangle.computeNormal();
      triangles.push_back(triangle);

      // Map all the vertices of the triangle to the triangle.
      vecTriMap.insert(vecTriPair_t(this->vertices.at(i + 0), &triangles.back()));
      vecTriMap.insert(vecTriPair_t(this->vertices.at(i + 1), &triangles.back()));
      vecTriMap.insert(vecTriPair_t(this->vertices.at(i + 2), &triangles.back()));
    }

    // All the normals and tangents are initialized to 0,0,0.
    this->vertexNormals.resize(this->vertices.size(),  vec3(0.0f, 0.0f, 0.0f));
    this->vertexTangents.resize(this->vertices.size(), vec3(0.0f, 0.0f, 0.0f));
    norm = this->vertexNormals.begin();
    tan  = this->vertexTangents.begin();

    // Compute the normal for vec.
    for (vecIt_t vec = this->vertices.begin(); vec != this->vertices.end(); ++vec)
    {
      // Find all the triangles that contain this vertex.
      vecRange = vecTriMap.equal_range(*vec);

      // Add all the face normals, then normalize the sum.
      for (vecTriMap_t::iterator it = vecRange.first; it != vecRange.second; ++it)
      {
        *norm += it->second->getFaceNormal();
        *tan  += it->second->getTangent();
      }

      *norm = normalize(*norm);
      *tan  = normalize(*tan);

      ++norm;
      ++tan;
    }
  }

  /**
   * Set the material of this object.
   * @param material The material to use for this object.
   */
  void WorldObject::setMaterial(unique_ptr<Material> material)
  {
    this->material = move(material);
  }

  /**
   * Get the material of this object.
   */
  Material& WorldObject::getMaterial() const
  {
    return *this->material;
  }
}

