#ifndef _BUSYBIN_OBSERVABLE_H_
#define _BUSYBIN_OBSERVABLE_H_

#include "Observer.h"
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * A basic type-safe Observable abstract class.
   */
  template <class ObservableType>
  class Observable
  {
    typedef vector<Observer<ObservableType>* > observableVec;
    typedef typename observableVec::iterator observableVecIt;
    observableVec observers;

  public:
    /**
     * Do-nothing destructor.
     */
    virtual ~Observable() {}

    /**
     * Add an observer.  The observer must stay alive - it is not copied!
     * @param observer An observer to add to the list.
     */
    virtual void addObserver(Observer<ObservableType>& observer)
    {
      observers.push_back(&observer);
      observer.notify(dynamic_cast<ObservableType*>(this));
    }

    /**
     * Notify all observers.
     */
    virtual void notifyObservers()
    {
      observableVecIt it  = this->observers.begin();
      observableVecIt end = this->observers.end();

      for (; it != end; ++it)
        (*it)->notify(dynamic_cast<ObservableType*>(this));
    }
  };
}

#endif

