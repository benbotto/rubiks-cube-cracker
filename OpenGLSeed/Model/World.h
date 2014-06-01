#ifndef _BUSYBIN_WORLD_H_
#define _BUSYBIN_WORLD_H_

#include "MatrixStack.h"
#include "../Util/GLException.h"
#include "../Controller/GL/Program/Program.h"
#include "../Util/Observable.h"
#include "WorldObject/WorldObject.h"
#include "Camera.h"
#include <iterator>
using std::iterator;
using std::random_access_iterator_tag;
#include <memory>
using std::unique_ptr;
using std::move;
#include <vector>
using std::vector;
#include <map>
using std::map;

namespace busybin
{
  /**
   * This class holds all the WorldObjects.
   */
  class World : public Observable<World>
  {
  protected:
    typedef unique_ptr<Program>     progPtr;
    typedef unique_ptr<WorldObject> woPtr;
    typedef vector<woPtr>           woVector;

  private:
    progPtr     program;
    woVector    worldObjs;
    Camera      camera;
    MatrixStack matrixStack;
    map<string, unsigned> woMap;

    World(const World& world);
    void operator=(const World&);
    World();

  public:
    /**
     * Allows iteration over the world.
     */
    class Iterator : public iterator<random_access_iterator_tag, int>
    {
      int    pos;
      World* world;

      Iterator();
    public:
      Iterator(const Iterator& it);
      Iterator(World& world);
      Iterator(World& world, unsigned pos);
      Iterator& operator++();
      Iterator operator++(int);
      Iterator& operator--();
      Iterator operator--(int);
      bool operator==(const Iterator& rhs);
      bool operator!=(const Iterator& rhs);
      WorldObject& operator*();
      WorldObject* operator->();
    };

    World(progPtr program);
    virtual ~World();
    virtual WorldObject& addWorldObject(woPtr worldObj);

    WorldObject& at(unsigned i);
    WorldObject& at(const string& name);
    WorldObject& operator[](unsigned i);
    WorldObject& operator[](const string& name);
    unsigned size() const;

    Iterator begin();
    Iterator end();
    Iterator back();

    virtual Program& getProgram();
    Camera& getCamera();
    MatrixStack& getMatrixStack();

    virtual void draw(double elapsed);
  };
}

#endif

