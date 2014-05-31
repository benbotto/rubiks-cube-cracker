#include "Cubie.h"

namespace busybin
{
  /**
   * Initialize the Cube.
   * @param pProgram The currently installed shader program.
   * @param pMatrixStack The World's MatrixStack.
   * @param name The name of this cubie.
   * @param position The position of this cubie.
   */
  Cubie::Cubie(Program* pProgram, MatrixStack* pMatrixStack,
    const string& name, const vec3& position) : 
    Cube(1.0f, pProgram, pMatrixStack, name, 
    {
      vec4(1.0f, 1.0f, 1.0f, 1.0f), // UP (W).
      vec4(0.0f, 1.0f, 0.0f, 1.0f), // LEFT (G).
      vec4(1.0f, 0.0f, 0.0f, 1.0f), // FRONT (R).
      vec4(0.0f, 0.0f, 1.0f, 1.0f), // RIGHT (B).
      vec4(1.0f, 0.6f, 0.0f, 1.0f), // BACK (O).
      vec4(1.0f, 1.0f, 0.0f, 1.0f)  // DOWN (Y).
    })
  {
    this->translation = translate(mat4(1.0f), position);
    this->setMaterial(unique_ptr<Material>(new GrayPlastic()));
  }

  /**
   * Draw the Cubie.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Cubie::draw(double elapsed)
  {
    // Set up the MVP.
    this->getMatrixStack()->pushModel();
    this->getMatrixStack()->topModel() *= this->translation;
    this->getProgram()->setMVP(*this->getMatrixStack());
    this->getMatrixStack()->popModel();

    // The translation is needed for the hidden sides.
    this->getProgram()->setUniform("cubieTranslation", this->translation);

    // Install the material.
    this->getProgram()->setUniform("material", this->getMaterial());

    // Draw the object.
    this->getProgram()->drawArrays(this->getVAO(), this->vertices.size());
  }

  /**
   * Return the program (downcast).
   */
  RubiksCubeProgram* Cubie::getProgram() const
  {
    return dynamic_cast<RubiksCubeProgram*>(WorldObject::getProgram());
  }
}

