#ifndef _BUSYBIN_MOVE_STORE_H_
#define _BUSYBIN_MOVE_STORE_H_

#include "../../Util/RubiksCubeException.h"
#include <vector>
using std::vector;
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
    typedef map<string, moveFunc_t> moveFuncMap_t;
    typedef map<string, string>     invMove_t;

  protected:
    virtual moveFuncMap_t& getMoveMap() = 0;

  public:
    MoveStore();

    virtual const vector<string>& getMoves() const = 0;
    virtual const invMove_t& getInverseMoves() const = 0;
    string getMove(unsigned ind) const;
    string getInverseMove(const string& move) const;
    virtual unsigned getNumMoves() const;

    virtual const moveFuncMap_t& getMoveMap() const = 0;
    bool isValidMove(const string& move) const;
    moveFunc_t& getMoveFunc(const string& move);
    moveFunc_t& getInverseMoveFunc(const string& move);

    virtual void move(uint8_t ind);
    virtual void invert(uint8_t ind);
  };
}

#endif

