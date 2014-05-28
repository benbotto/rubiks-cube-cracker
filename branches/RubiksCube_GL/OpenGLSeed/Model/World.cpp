#include "World.h"

namespace busybin
{
  /**
   * Prevent copies.
   */
  World::World(const World& world) {}

  /**
   * Prevent copies.
   */
  void World::operator=(const World&) {}

  /**
   * No default constructor.
   */
  World::World() {}

  /**
   * Poplulate the world.
   */
  World::World(unique_ptr<Program> program)
  {
    this->program = move(program);
  }

  /**
   * Destroy the world (WorldObjecs are cleaned up by their container).
   */
  World::~World() {}

  /**
   * Get an instance of the world.
   * @param worldObj The WorldObject to add.  Ownership is taken, and the
   *        object is automatically deleted when the World is destructed.  The
   *        name of the world object must be unique.
   */
  WorldObject& World::addWorldObject(unique_ptr<WorldObject> worldObj)
  {
    if (this->woMap.count(worldObj->getName()))
      throw GLException("WorldObject names must be unique.");

    this->woMap[worldObj->getName()] = this->worldObjs.size();
    this->worldObjs.push_back(move(worldObj));

    return *this->worldObjs.back();
  }

  /**
   * Access the object at i.
   * @param i Position of the WorldObject to access.
   */
  WorldObject& World::at(unsigned i)
  {
    if (i >= this->size() || i < 0)
      throw GLException("Index out of bounds.");

    return *this->worldObjs.at(i);
  }

  /**
   * Access the object at name.
   * @param name The name of a WorldObject.
   */
  WorldObject& World::at(const string& name)
  {
    map<string, unsigned>::const_iterator index = this->woMap.find(name);

    if (index == this->woMap.end())
      throw GLException("Index out of bounds.  Invalid WorldObject name.");
    else
      return this->at(index->second);
  }

  /**
   * Access the object at i.
   * @param i Position of the WorldObject to access.
   */
  WorldObject& World::operator[](unsigned i)
  {
    return this->at(i);
  }

  /**
   * Access the object at name.
   * @param name The name of a WorldObject to find.
   */
  WorldObject& World::operator[](const string& name)
  {
    return this->at(name);
  }

  /**
   * Get the number of world objects.
   */
  unsigned World::size() const
  {
    return this->worldObjs.size();
  }

  /**
   * Get an iterator pointing at the beginning.
   */
  World::Iterator World::begin()
  {
    return World::Iterator(*this);
  }

  /**
   * Get an iterator pointing at the end (one after the last).
   */
  World::Iterator World::end()
  {
    return World::Iterator(*this, this->size());
  }

  /**
   * Get an iterator pointing at the back (last element).
   */
  World::Iterator World::back()
  {
    return World::Iterator(*this, this->size() - 1);
  }

  /**
   * Get the currently installed shader program.
   */
  Program& World::getProgram()
  {
    return *this->program;
  }

  /**
   * Get the World's Camera.
   */
  Camera& World::getCamera()
  {
    return this->camera;
  }

  /**
   * Get the World's MatrixStack.
   */
  MatrixStack& World::getMatrixStack()
  {
    return this->matrixStack;
  }

  /**
   * Draw each WorldObject in the world.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void World::draw(double elapsed)
  {
    World::Iterator end = this->end();

    // Draw the WorldObjects.
    for (World::Iterator it = this->begin(); it != end; ++it)
      it->draw(elapsed);
  }
}

