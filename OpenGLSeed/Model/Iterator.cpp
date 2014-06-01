#include "World.h"

namespace busybin
{
  /**
   * Copy constructor - copy the world and position.
   * @param it An iterator to be copied.
   */
  World::Iterator::Iterator(const World::Iterator& it)
  {
    pos   = it.pos;
    world = it.world;
  }

  /**
   * Start a the beginning of world.
   * @param world Reference to the World.
   */
  World::Iterator::Iterator(World& world)
  {
    pos         = 0;
    this->world = &world;
  }

  /**
   * Start at pos in world.
   * @param world Reference to the World.
   * @param pos The position of the WorldObject in the World at which
   * iteration should begin.
   */
  World::Iterator::Iterator(World& world, unsigned pos)
  {
    this->pos   = pos;
    this->world = &world;
  }

  /**
   * Pre increment.
   */
  World::Iterator& World::Iterator::operator++()
  {
    ++pos;
    return *this;
  }

  /**
   * Post increment.
   */
  World::Iterator World::Iterator::operator++(int)
  {
    Iterator temp(*this);
    ++pos;
    return temp;
  }

  /**
   * Pre decrement.
   */
  World::Iterator& World::Iterator::operator--()
  {
    --pos;
    return *this;
  }

  /**
   * Post decrement.
   */
  World::Iterator World::Iterator::operator--(int)
  {
    Iterator temp(*this);
    --pos;
    return temp;
  }

  /**
   * Comparison operator.
   * @param rhs Iterator to compare to.
   */
  bool World::Iterator::operator==(const World::Iterator& rhs)
  {
    return pos == rhs.pos;
  }

  /**
   * Not equal.
   * @param rhs Iterator to compare to.
   */
  bool World::Iterator::operator!=(const World::Iterator& rhs)
  {
    return pos != rhs.pos;
  }

  /**
   * Dereference.
   */
  WorldObject& World::Iterator::operator*()
  {
    return world->at(pos);
  }

  /**
   * Dereference.
   */
  WorldObject* World::Iterator::operator->()
  {
    return &world->at(pos);
  }
}
