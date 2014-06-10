#ifndef _BUSYBIN_MOVE_STORE_H_
#define _BUSYBIN_MOVE_STORE_H_

#include "../../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <string>
using std::string;
#include <map>
using std::map;
#include <functional>
using std::function;
using std::bind;

namespace busybin
{
  /**
   * Base class for the MoveStore classes.
   */
  class MoveStore
  {
  public:
    typedef function<void()>        moveFunc_t;
    typedef function<void()>        rotFunc_t;
    typedef map<string, moveFunc_t> moveMap_t;
    typedef map<string, rotFunc_t>  rotMap_t;
    typedef map<string, string>     invMove_t;
    typedef map<string, string>     invRot_t;

  private:
    array<string, 18> moves;
    invMove_t         inverseMoves;
    array<string, 9>  rotations;
    invRot_t          inverseRotations;

  protected:
    virtual moveMap_t& getMoveMap() = 0;
    virtual moveMap_t& getRotationMap() = 0;

  public:
    MoveStore();

    const array<string, 18>& getMoves() const;
    string getMove(unsigned ind) const;
    string getInverseMove(const string& move) const;
    unsigned getNumMoves() const;

    virtual const moveMap_t& getMoveMap() const = 0;
    bool isValidMove(const string& move) const;
    moveFunc_t& getMoveFunc(const string& move);
    moveFunc_t& getInverseMoveFunc(const string& move);

    const array<string, 9>& getRotations() const;
    string getRotation(unsigned ind) const;
    string getInverseRotation(const string& rotation) const;
    unsigned getNumRotations() const;

    virtual const rotMap_t& getRotationMap() const = 0;
    bool isValidRotation(const string& rotation) const;
    rotFunc_t& getRotationFunc(const string& rotation);
    rotFunc_t& getInverseRotationFunc(const string& rotation);
  };
}

#endif

